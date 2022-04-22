#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For loop on all of the pixels;
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++) {
            // Calculating average and rounding it up since its float;
            float avg = round((image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed) / 3.0);

            // Assigning the new values;
            image[r][c].rgbtBlue = avg;
            image[r][c].rgbtGreen = avg;
            image[r][c].rgbtRed = avg;
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For loop on all the pixels;
    for (int r = 0; r < height; r++)
    // Width/2 because I am looping from left to middle, and from right to middle, both at the same time;
        for (int c = 0; c < (width/2); c++) {
            // Assigning values into a temp variable to swap;
            RGBTRIPLE temp;
            temp.rgbtBlue = image[r][c].rgbtBlue;
            temp.rgbtGreen = image[r][c].rgbtGreen;
            temp.rgbtRed = image[r][c].rgbtRed;

            // Swapping left with right;
            image[r][c].rgbtBlue = image[r][width-c-1].rgbtBlue;
            image[r][c].rgbtGreen = image[r][width-c-1].rgbtGreen;
            image[r][c].rgbtRed = image[r][width-c-1].rgbtRed;

            // Swapping right with what was left;
            image[r][width-c-1].rgbtBlue = temp.rgbtBlue;
            image[r][width-c-1].rgbtGreen = temp.rgbtGreen;
            image[r][width-c-1].rgbtRed = temp.rgbtRed;
        }
    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy;
    RGBTRIPLE tmpImg[height][width];

    // For loop on all the pixels;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Defining colors;
            int totalBlue = 0, totalGreen = 0, totalRed = 0;

            // Defining total number of pixels;
            float total = 0.0;

            for (int i = r - 1; i < r + 2; i++)
            {
                for (int j = c - 1; j < c + 2; j++)
                {
                    // Skipping out of boundary pixels;
                    if (i < 0 || j < 0 || i >= height || j >= width) { continue; }
                    else
                    {
                        totalRed += image[i][j].rgbtRed;     // Calculating total blue;
                        totalGreen += image[i][j].rgbtGreen;     // Calculating total green;
                        totalBlue += image[i][j].rgbtBlue;       // Calculating total red;
                        total++;  // Calculating pixels;
                    }
                    // Assigning the new values;
            tmpImg[r][c].rgbtRed = round(totalRed/total);
            tmpImg[r][c].rgbtGreen = round(totalGreen/total);
            tmpImg[r][c].rgbtBlue = round(totalBlue/total);
                }
            }
        }
    }

    // Ultimately, moving the values from the copy image to the original;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            image[r][c].rgbtBlue = tmpImg[r][c].rgbtBlue;
            image[r][c].rgbtGreen = tmpImg[r][c].rgbtGreen;
            image[r][c].rgbtRed = tmpImg[r][c].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Making a copy;
    RGBTRIPLE tmpImg[height][width];

    // Creating Kernel matrices;
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Looping on all pixels;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // Defining colors, and co-ords;
            int rowCoords[3] = { r-1 , r, r+1 };
            int colCoords[3] = { c-1, c, c+1 };
            float redGx = 0, greenGx = 0, blueGx = 0;
            float redGy = 0, greenGy = 0, blueGy = 0;

            // Algorithm part one, doing calculations;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    // Current;
                    int currRow = rowCoords[i];
                    int currCol = colCoords[j];

                    // Skipping out of boundary pixels;
                    if (currRow >= 0 && currRow < height && currCol >= 0 && currCol < width) {
                        RGBTRIPLE pixel = image[currRow][currCol];

                        redGx += Gx[i][j] * pixel.rgbtRed;     // Calculating total blue;
                        greenGx += Gx[i][j] * pixel.rgbtGreen;     // Calculating total green;
                        blueGx += Gx[i][j] * pixel.rgbtBlue;       // Calculating total red;

                        redGy += Gy[i][j] * pixel.rgbtRed;     // Calculating total blue;
                        greenGy += Gy[i][j] * pixel.rgbtGreen;     // Calculating total green;
                        blueGy += Gy[i][j] * pixel.rgbtBlue;       // Calculating total red;
                    }
                }
            }

            // Algorithm part two, final sqrt calculations;
            int finalRed = round(sqrt(redGx*redGx + redGy*redGy));
            int finalGreen = round(sqrt(greenGx*greenGx + greenGy*greenGy));
            int finalBlue = round(sqrt(blueGx*blueGx + blueGy*blueGy));

            tmpImg[r][c].rgbtRed = finalRed > 255 ? 255: finalRed; // Stay in range;
            tmpImg[r][c].rgbtGreen = finalGreen > 255 ? 255: finalGreen; // Stay in range;
            tmpImg[r][c].rgbtBlue = finalBlue > 255 ? 255: finalBlue; // Stay in range;
        }
    }

    // Ultimately, moving the values from the copy image to the original;
    for (int r = 0; r < height; r++)
    for (int c = 0; c < width; c++)
    {
        image[r][c].rgbtBlue = tmpImg[r][c].rgbtBlue; // For blue;
        image[r][c].rgbtGreen = tmpImg[r][c].rgbtGreen; // For green;
        image[r][c].rgbtRed = tmpImg[r][c].rgbtRed; // For red;
    }
    return;
}
