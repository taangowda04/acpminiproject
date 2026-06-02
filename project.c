#include <stdio.h>

#define ROWS 6
#define COLS 20

typedef struct {
    int length;
    int width;
    int radius;
    int x1, x2, x3, y1, y2, y3;
    int a1, a2, b1, b2;
} dimension;

char pic[ROWS][COLS];

void drawCircle();
void drawRectangle();
void drawLine();
void drawTriangle();
void addObject();
void deleteObject();
void modifyObject();

void clearPicture()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            pic[i][j] = '-';
        }
    }
}

void displayPicture()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", pic[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    dimension dim;

    printf("Shapes:\n");

    printf("Circle:\n");
    printf("Enter radius: ");
    scanf("%d", &dim.radius);

    printf("\nFor Rectangle:\n");
    printf("Enter length and width: ");
    scanf("%d%d", &dim.length, &dim.width);

    printf("\nFor Line:\n");
    printf("Enter coordinates of two points: ");
    scanf("%d%d%d%d", &dim.a1, &dim.b1, &dim.a2, &dim.b2);

    printf("\nFor Triangle:\n");
    printf("Enter coordinates of three points:\n");

    printf("1st point coordinates: ");
    scanf("%d%d", &dim.x1, &dim.y1);

    printf("2nd point coordinates: ");
    scanf("%d%d", &dim.x2, &dim.y2);

    printf("3rd point coordinates: ");
    scanf("%d%d", &dim.x3, &dim.y3);

    return 0;
}