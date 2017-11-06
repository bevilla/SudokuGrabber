#include	<opencv2/imgproc.hpp>

#include	"SudokuGrabber.hpp"

namespace sg
{
  void		calculateIntersections(const cv::Size &matSize,
				       const SudokuEdges &edges,
				       cv::Point2f src[],
                       cv::Point2f dest[],
                       int *maxLength)
  {
     cv::Point left1, left2, right1, right2, bottom1, bottom2, top1, top2;

    int height = matSize.height;
    int width = matSize.width;

    if (edges.left[1]!=0)
    {
        left1.x = 0;
        left1.y = edges.left[0]/sin(edges.left[1]);
        left2.x = width;
        left2.y =- left2.x/tan(edges.left[1]) + left1.y;
    }
    else
    {
        left1.y = 0;
        left1.x = edges.left[0]/cos(edges.left[1]);
        left2.y = height;
        left2.x = left1.x - height*tan(edges.left[1]);
    }

    if (edges.right[1]!=0)
    {
        right1.x = 0;
        right1.y = edges.right[0]/sin(edges.right[1]);
        right2.x = width;
        right2.y =- right2.x/tan(edges.right[1]) + right1.y;
    }
    else
    {
        right1.y = 0;
        right1.x = edges.right[0]/cos(edges.right[1]);
        right2.y = height;
        right2.x = right1.x - height*tan(edges.right[1]);
    }

    bottom1.x = 0;
    bottom1.y = edges.bottom[0]/sin(edges.bottom[1]);
    bottom2.x = width;bottom2.y=-bottom2.x/tan(edges.bottom[1]) + bottom1.y;

    top1.x = 0;
    top1.y = edges.top[0]/sin(edges.top[1]);
    top2.x = width;
    top2.y =- top2.x/tan(edges.top[1]) + top1.y;

    // NEXT

    // Next, we find the intersection of  these four lines
    double leftA = left2.y-left1.y;
    double leftB = left1.x-left2.x;

    double leftC = leftA*left1.x + leftB*left1.y;

    double rightA = right2.y-right1.y;
    double rightB = right1.x-right2.x;

    double rightC = rightA*right1.x + rightB*right1.y;

    double topA = top2.y-top1.y;
    double topB = top1.x-top2.x;

    double topC = topA*top1.x + topB*top1.y;

    double bottomA = bottom2.y-bottom1.y;
    double bottomB = bottom1.x-bottom2.x;

    double bottomC = bottomA*bottom1.x + bottomB*bottom1.y;

    // Intersection of left and top
    double detTopLeft = leftA*topB - leftB*topA;

    CvPoint ptTopLeft = cvPoint((topB*leftC - leftB*topC)/detTopLeft, (leftA*topC - topA*leftC)/detTopLeft);

    // Intersection of top and right
    double detTopRight = rightA*topB - rightB*topA;

    CvPoint ptTopRight = cvPoint((topB*rightC-rightB*topC)/detTopRight, (rightA*topC-topA*rightC)/detTopRight);

    // Intersection of right and bottom
    double detBottomRight = rightA*bottomB - rightB*bottomA;
    CvPoint ptBottomRight = cvPoint((bottomB*rightC-rightB*bottomC)/detBottomRight, (rightA*bottomC-bottomA*rightC)/detBottomRight);// Intersection of bottom and left
    double detBottomLeft = leftA*bottomB-leftB*bottomA;
    CvPoint ptBottomLeft = cvPoint((bottomB*leftC-leftB*bottomC)/detBottomLeft, (leftA*bottomC-bottomA*leftC)/detBottomLeft);

    *maxLength = (ptBottomLeft.x-ptBottomRight.x)*(ptBottomLeft.x-ptBottomRight.x) + (ptBottomLeft.y-ptBottomRight.y)*(ptBottomLeft.y-ptBottomRight.y);
    int temp = (ptTopRight.x-ptBottomRight.x)*(ptTopRight.x-ptBottomRight.x) + (ptTopRight.y-ptBottomRight.y)*(ptTopRight.y-ptBottomRight.y);

    if (temp > (*maxLength)) (*maxLength) = temp;

    temp = (ptTopRight.x-ptTopLeft.x)*(ptTopRight.x-ptTopLeft.x) + (ptTopRight.y-ptTopLeft.y)*(ptTopRight.y-ptTopLeft.y);

    if (temp > (*maxLength)) (*maxLength) = temp;

    temp = (ptBottomLeft.x-ptTopLeft.x)*(ptBottomLeft.x-ptTopLeft.x) + (ptBottomLeft.y-ptTopLeft.y)*(ptBottomLeft.y-ptTopLeft.y);

    if (temp > (*maxLength)) (*maxLength) = temp;

    *maxLength = sqrt((double)(*maxLength));

    src[0] = ptTopLeft;         dest[0] = cv::Point2f(0,0);
    src[1] = ptTopRight;        dest[1] = cv::Point2f((*maxLength) - 1, 0);
    src[2] = ptBottomRight;     dest[2] = cv::Point2f((*maxLength) - 1, (*maxLength) - 1);
    src[3] = ptBottomLeft;      dest[3] = cv::Point2f(0, (*maxLength) - 1);
  }
};
