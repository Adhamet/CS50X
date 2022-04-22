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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // For loop on all of the pixels;
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++) {
            // Writing down the rules and rounding them up;
            float sepiaRed = round((0.393 * image[r][c].rgbtRed) + (0.769 * image[r][c].rgbtGreen) + (0.189 * image[r][c].rgbtBlue));
            float sepiaGreen = round((0.349 * image[r][c].rgbtRed) + (0.686 * image[r][c].rgbtGreen) + (0.168 * image[r][c].rgbtBlue));
            float sepiaBlue = round((0.272 * image[r][c].rgbtRed) + (0.534 * image[r][c].rgbtGreen) + ( 0.131 * image[r][c].rgbtBlue));

            // Using if statements to make sure it doesnt exceed the ordinary 255 pixel value;
            sepiaRed = sepiaRed > 255? 255 : sepiaRed;
            sepiaGreen = sepiaGreen > 255? 255 : sepiaGreen;
            sepiaBlue = sepiaBlue > 255? 255 : sepiaBlue;

            // Assigning the new values;
            image[r][c].rgbtRed = sepiaRed;
            image[r][c].rgbtGreen = sepiaGreen;
            image[r][c].rgbtBlue = sepiaBlue;
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
    RGBTRIPLE tmpImg[height][width];
    // For loop on all the pixels;
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++) {
            // Defining colors;
            int totalBlue = 0, totalGreen = 0, totalRed = 0;
            // Defining total number of pixels;
            float total = 0.0;
            for (int i = r - 1; i < r + 2; i++)
                for (int j = c - 1; j < c + 2; j++) {
                    // Skipping out of boundary pixels;
                    if (i < 0 || j < 0 || i >= height || j >= width) { continue; }
                    else { totalRed += image[i][j].rgbtRed;     // Calculating total blue;
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
    // Finally moving the values from the copy image to the original;
    for (int r = 0; r < height; r++)
    for (int c = 0; c < width; c++) {
        image[r][c].rgbtBlue = tmpImg[r][c].rgbtBlue;
        image[r][c].rgbtGreen = tmpImg[r][c].rgbtGreen;
        image[r][c].rgbtRed = tmpImg[r][c].rgbtRed;
    }
    return;
}

