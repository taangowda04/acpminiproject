#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ROWS 30
#define COLS 60
typedef struct {
    int length;
    int width;
    int radius;
    int x1, x2, x3, y1, y2, y3;   
    int a1, a2, b1, b2;            
    int cx, cy;                     
    int rx, ry;                  
} dimension;
char pic[ROWS][COLS];
void clearPicture();
void displayPicture();
void putPixel(int x, int y, char c);
void drawCircle(dimension dim);
void drawRectangle(dimension dim);
void drawLine(dimension dim);
void drawTriangle(dimension dim);
void fillCircle(dimension dim);
void fillRectangle(dimension dim);
void fillTriangle(dimension dim);
void inputAll(dimension *dim);
void clearPicture()
{
    int i, j;
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            pic[i][j] = ' ';
}
void displayPicture()
{
    int i, j;
    printf("\n    ");
    for (j = 0; j < COLS; j++)
        printf("%d", j % 10);
    printf("\n");
    printf("   +");
    for (j = 0; j < COLS; j++)
        printf("-");
    printf("+\n");
    for (i = 0; i < ROWS; i++)
    {
        printf("%2d |", i);
        for (j = 0; j < COLS; j++)
            printf("%c", pic[i][j]);
        printf("|\n");
    }
    printf("   +");
    for (j = 0; j < COLS; j++)
        printf("-");
    printf("+\n");
}
void putPixel(int x, int y, char c)
{
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS)
        pic[y][x] = c;
}
void fillCircle(dimension dim)
{
    int x, y;
    int cx = dim.cx;
    int cy = dim.cy;
    int r = dim.radius;
    int r2 = r * r;
    if (r <= 0) return;
    for (y = cy - r; y <= cy + r; y++)
    {
        for (x = cx - r; x <= cx + r; x++)
        {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy < r2)
            {
                putPixel(x, y, '-');
            }
        }
    }
}
void fillRectangle(dimension dim)
{
    int i, j;
    int x = dim.rx;
    int y = dim.ry;
    int w = dim.length;
    int h = dim.width;
    if (w <= 0 || h <= 0) return;
    for (i = y + 1; i < y + h; i++)
    {
        for (j = x + 1; j < x + w; j++)
        {
            putPixel(j, i, '-');
        }
    }
}
void fillTriangle(dimension dim)
{
    int x1 = dim.x1, y1 = dim.y1;
    int x2 = dim.x2, y2 = dim.y2;
    int x3 = dim.x3, y3 = dim.y3;
    int minY, maxY, y;
    int temp;
    minY = y1;
    if (y2 < minY) minY = y2;
    if (y3 < minY) minY = y3;
    maxY = y1;
    if (y2 > maxY) maxY = y2;
    if (y3 > maxY) maxY = y3;
    for (y = minY; y <= maxY; y++)
    {
        int xIntersect[6];
        int count = 0;
        int i, j;
        if ((y1 <= y && y < y2) || (y2 <= y && y < y1))
        {
            if (y1 != y2)
                xIntersect[count++] = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
        }
        if ((y2 <= y && y < y3) || (y3 <= y && y < y2))
        {
            if (y2 != y3)
                xIntersect[count++] = x2 + (y - y2) * (x3 - x2) / (y3 - y2);
        }
        if ((y3 <= y && y < y1) || (y1 <= y && y < y3))
        {
            if (y3 != y1)
                xIntersect[count++] = x3 + (y - y3) * (x1 - x3) / (y1 - y3);
        }
        for (i = 0; i < count - 1; i++)
        {
            for (j = i + 1; j < count; j++)
            {
                if (xIntersect[i] > xIntersect[j])
                {
                    temp = xIntersect[i];
                    xIntersect[i] = xIntersect[j];
                    xIntersect[j] = temp;
                }
            }
        }
        for (i = 0; i + 1 < count; i += 2)
        {
            for (j = xIntersect[i]; j <= xIntersect[i + 1]; j++)
            {
                putPixel(j, y, '-');
            }
        }
    }
}
void drawCircle(dimension dim)
{
    int x = dim.radius;
    int y = 0;
    int err = 1 - dim.radius;
    int cx = dim.cx;
    int cy = dim.cy;
    if (dim.radius <= 0) return;
    while (x >= y)
    {
        putPixel(cx + x, cy + y, '*');
        putPixel(cx - x, cy + y, '*');
        putPixel(cx + x, cy - y, '*');
        putPixel(cx - x, cy - y, '*');
        putPixel(cx + y, cy + x, '*');
        putPixel(cx - y, cy + x, '*');
        putPixel(cx + y, cy - x, '*');
        putPixel(cx - y, cy - x, '*');
        y++;
        if (err < 0)
            err += 2 * y + 1;
        else
        {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}
void drawRectangle(dimension dim)
{
    int i;
    int x = dim.rx;
    int y = dim.ry;
    int w = dim.length;
    int h = dim.width;
    if (w <= 0 || h <= 0) return;
    for (i = 0; i <= w; i++)
    {
        putPixel(x + i, y, '_');
        putPixel(x + i, y + h, '_');
    }
    for (i = 0; i <= h; i++)
    {
        putPixel(x, y + i, '*');
        putPixel(x + w, y + i, '*');
    }
}
void drawLine(dimension dim)
{
    int x1 = dim.a1, y1 = dim.b1;
    int x2 = dim.a2, y2 = dim.b2;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;
    while (1)
    {
        putPixel(x1, y1, '*');
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 <  dx) { err += dx; y1 += sy; }
    }
}
void drawTriangle(dimension dim)
{
    dimension line;
    line.a1 = dim.x1; line.b1 = dim.y1;
    line.a2 = dim.x2; line.b2 = dim.y2;
    drawLine(line);
    line.a1 = dim.x2; line.b1 = dim.y2;
    line.a2 = dim.x3; line.b2 = dim.y3;
    drawLine(line);
    line.a1 = dim.x3; line.b1 = dim.y3;
    line.a2 = dim.x1; line.b2 = dim.y1;
    drawLine(line);
}
void drawAllShapes(dimension dim)
{
    clearPicture();
    fillCircle(dim);
    fillRectangle(dim);
    fillTriangle(dim);
    drawCircle(dim);
    drawRectangle(dim);
    drawLine(dim);
    drawTriangle(dim);
}
void inputAll(dimension *dim)
{
    printf("CANVAS SIZE: %d rows (y: 0-%d) x %d cols (x: 0-%d)\n\n",
            ROWS, ROWS - 1, COLS, COLS - 1);
    printf("CIRCLE:\n");
    printf("  Enter center x (col): ");
    scanf("%d", &dim->cx);
    printf("  Enter center y (row): ");
    scanf("%d", &dim->cy);
    printf("  Enter radius: ");
    scanf("%d", &dim->radius);
    printf("\nRECTANGLE:\n");
    printf("  Enter top-left x (col): ");
    scanf("%d", &dim->rx);
    printf("  Enter top-left y (row): ");
    scanf("%d", &dim->ry);
    printf("  Enter length (horizontal): ");
    scanf("%d", &dim->length);
    printf("  Enter width (vertical): ");
    scanf("%d", &dim->width);
    printf("\nLINE:\n");
    printf("  Enter start x: ");
    scanf("%d", &dim->a1);
    printf("  Enter start y: ");
    scanf("%d", &dim->b1);
    printf("  Enter end x: ");
    scanf("%d", &dim->a2);
    printf("  Enter end y: ");
    scanf("%d", &dim->b2);
    printf("\nTRIANGLE:\n");
    printf("  1st point x: "); scanf("%d", &dim->x1);
    printf("  1st point y: "); scanf("%d", &dim->y1);
    printf("  2nd point x: "); scanf("%d", &dim->x2);
    printf("  2nd point y: "); scanf("%d", &dim->y2);
    printf("  3rd point x: "); scanf("%d", &dim->x3);
    printf("  3rd point y: "); scanf("%d", &dim->y3);
}
void addObject(dimension *dim)
{
    int choice;
    printf("\nWhich shape to ADD/REPLACE?\n");
    printf("  1) Circle  2) Rectangle  3) Line  4) Triangle\n");
    printf("  Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            printf("  New center x: "); scanf("%d", &dim->cx);
            printf("  New center y: "); scanf("%d", &dim->cy);
            printf("  New radius:   "); scanf("%d", &dim->radius);
            break;
        case 2:
            printf("  New top-left x: "); scanf("%d", &dim->rx);
            printf("  New top-left y: "); scanf("%d", &dim->ry);
            printf("  New length:     "); scanf("%d", &dim->length);
            printf("  New width:      "); scanf("%d", &dim->width);
            break;
        case 3:
            printf("  New start x: "); scanf("%d", &dim->a1);
            printf("  New start y: "); scanf("%d", &dim->b1);
            printf("  New end x:   "); scanf("%d", &dim->a2);
            printf("  New end y:   "); scanf("%d", &dim->b2);
            break;
        case 4:
            printf("  New V1 x: "); scanf("%d", &dim->x1);
            printf("  New V1 y: "); scanf("%d", &dim->y1);
            printf("  New V2 x: "); scanf("%d", &dim->x2);
            printf("  New V2 y: "); scanf("%d", &dim->y2);
            printf("  New V3 x: "); scanf("%d", &dim->x3);
            printf("  New V3 y: "); scanf("%d", &dim->y3);
            break;
        default:
            printf("  Invalid!\n");
    }
}
void deleteObject(dimension *dim)
{
    int choice;
    printf("\nWhich shape to DELETE?\n");
    printf("  1) Circle  2) Rectangle  3) Line  4) Triangle\n");
    printf("  Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            dim->radius = 0;
            break;
        case 2:
            dim->length = 0;
            dim->width = 0;
            break;
        case 3:
            dim->a1 = dim->b1 = dim->a2 = dim->b2 = -1;
            break;
        case 4:
            dim->x1 = dim->y1 = dim->x2 = dim->y2 = dim->x3 = dim->y3 = -1;
            break;
        default:
            printf("  Invalid!\n");
            return;
    }
    printf("  -> Shape deleted.\n");
}
void modifyObject(dimension *dim)
{
    int choice;
    printf("\nWhich shape to MODIFY?\n");
    printf("  1) Circle  2) Rectangle  3) Line  4) Triangle\n");
    printf("  Choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            printf("  Current: center(%d,%d) radius=%d\n",
                    dim->cx, dim->cy, dim->radius);
            printf("  New center x: "); scanf("%d", &dim->cx);
            printf("  New center y: "); scanf("%d", &dim->cy);
            printf("  New radius:   "); scanf("%d", &dim->radius);
            break;
        case 2:
            printf("  Current: pos(%d,%d) len=%d wid=%d\n",
                    dim->rx, dim->ry, dim->length, dim->width);
            printf("  New top-left x: "); scanf("%d", &dim->rx);
            printf("  New top-left y: "); scanf("%d", &dim->ry);
            printf("  New length:     "); scanf("%d", &dim->length);
            printf("  New width:      "); scanf("%d", &dim->width);
            break;
        case 3:
            printf("  Current: (%d,%d)->(%d,%d)\n",
                    dim->a1, dim->b1, dim->a2, dim->b2);
            printf("  New start x: "); scanf("%d", &dim->a1);
            printf("  New start y: "); scanf("%d", &dim->b1);
            printf("  New end x:   "); scanf("%d", &dim->a2);
            printf("  New end y:   "); scanf("%d", &dim->b2);
            break;
        case 4:
            printf("  Current: (%d,%d)(%d,%d)(%d,%d)\n",
                    dim->x1, dim->y1, dim->x2, dim->y2, dim->x3, dim->y3);
            printf("  New V1 x: "); scanf("%d", &dim->x1);
            printf("  New V1 y: "); scanf("%d", &dim->y1);
            printf("  New V2 x: "); scanf("%d", &dim->x2);
            printf("  New V2 y: "); scanf("%d", &dim->y2);
            printf("  New V3 x: "); scanf("%d", &dim->x3);
            printf("  New V3 y: "); scanf("%d", &dim->y3);
            break;
        default:
            printf("  Invalid!\n");
    }
}
int main()
{
    dimension dim = {0};
    int choice;
    printf("\n2D GRAPHICS EDITOR(* and _)\n\n");
    dim.a1 = dim.b1 = dim.a2 = dim.b2 = -1;
    dim.x1 = dim.y1 = dim.x2 = dim.y2 = dim.x3 = dim.y3 = -1;
    inputAll(&dim);
    drawAllShapes(dim);
    printf("\n==ALL SHAPES ON ONE CANVAS==\n");
    displayPicture();
    while (1)
    {
        printf("\n  1) Add    2) Delete    3) Modify    4) Display    5) Exit\n");
        printf("  Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                addObject(&dim);
                break;
            case 2:
                deleteObject(&dim);
                break;
            case 3:
                modifyObject(&dim);
                break;
            case 4:
                drawAllShapes(dim);
                displayPicture();
                break;
            case 5:
                printf("\n Tata bye byee!\n");
                return 0;
            default:
                printf("  Invalid!\n");
                continue;
        }
        drawAllShapes(dim);
        displayPicture();
    }
    return 0;
}