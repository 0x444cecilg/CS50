#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find average of each pixel
            int ave = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float) 3);

            // Set pixel colors equal to average
            image[i][j].rgbtRed = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtBlue = ave;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate through rows of image
    for (int i = 0; i < height; i++)
    {
        //iterate through each pixel in image
        for (int j = 0; j < width; j++)
        {

            //find the sepia value for each pixel
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            // Restrict color value to 0 - 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // Apply sepia value to original color value
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE rflt;
    // Iterate through rows in image
    for (int i = 0; i < height; i++)
    {
        // Iterate through pixels in image
        for (int j = 0; j < width / 2; j++)
        {
            // Swap 1st pixel for last pixel & 2nd pixel for 2nd to last... etc
            rflt = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = rflt;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of original image
    RGBTRIPLE blur[height][width];
    int redBlur;
    int greenBlur;
    int blueBlur;

    // Iterate through rows
    for (int i = 0; i < height - 1; i++)
    {
        // Iterate through pixels
        for (int j = 0; j < width - 1; j++)
        {
            blur[i][j].rgbtRed = image[i][j].rgbtRed;
            blur[i][j].rgbtGreen = image[i][j].rgbtGreen;
            blur[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Top left corner pixel
            if (i == 0 && j == 0)
            {
                redBlur = image[i][j].rgbtRed;
                redBlur += image[i+1][j].rgbtRed;
                redBlur += image[i][j+1].rgbtRed;
                redBlur += image[i+1][j+1].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 4);

                greenBlur = image[i][j].rgbtGreen;
                greenBlur += image[i+1][j].rgbtGreen;
                greenBlur += image[i][j+1].rgbtGreen;
                greenBlur += image[i+1][j+1].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 4);

                blueBlur = image[i][j].rgbtBlue;
                blueBlur += image[i+1][j].rgbtBlue;
                blueBlur += image[i][j+1].rgbtBlue;
                blueBlur += image[i+1][j+1].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 4);


            }
            // Lower left corner
            else if (i == (height - 1) && j == 0)
            {
                redBlur += image[i-1][j].rgbtRed;
                redBlur += image[i-1][j+1].rgbtRed;
                redBlur += image[i][j+1].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 4);

                greenBlur += image[i-1][j].rgbtGreen;
                greenBlur += image[i-1][j+1].rgbtGreen;
                greenBlur += image[i][j+1].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 4);

                blueBlur += image[i-1][j].rgbtBlue;
                blueBlur += image[i-1][j+1].rgbtBlue;
                blueBlur += image[i][j+1].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 4);


            }
            // Upper right corner
            else if (i == 0 && j == (width - 1))
            {
                redBlur += image[i][j-1].rgbtRed;
                redBlur += image[i+1][j].rgbtRed;
                redBlur += image[i+1][j-1].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 4);

                greenBlur += image[i][j-1].rgbtGreen;
                greenBlur += image[i+1][j].rgbtGreen;
                greenBlur += image[i+1][j-1].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 4);

                blueBlur += image[i][j-1].rgbtBlue;
                blueBlur += image[i+1][j].rgbtBlue;
                blueBlur += image[i+1][j-1].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 4);


            }
            // Lower right corner
            else if (i == (height - 1) && j == (width - 1))
            {
                redBlur += image[i-1][j].rgbtRed;
                redBlur += image[i][j-1].rgbtRed;
                redBlur += image[i-1][j-1].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 4);

                greenBlur += image[i][j-1].rgbtGreen;
                greenBlur += image[i+1][j].rgbtGreen;
                greenBlur += image[i-1][j-1].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 4);

                blueBlur += image[i][j-1].rgbtBlue;
                blueBlur += image[i+1][j].rgbtBlue;
                blueBlur += image[i-1][j-1].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 4);

            }
            // Left side
            else if (j == 0 && (i > 0 && i < height - 1))
            {
                redBlur += image[i-1][j].rgbtRed;
                redBlur += image[i-1][j+1].rgbtRed;
                redBlur += image[i][j+1].rgbtRed;
                redBlur += image[i+1][j].rgbtRed;
                redBlur += image[i+1][j+1].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 6);

                greenBlur += image[i-1][j].rgbtGreen;
                greenBlur += image[i-1][j+1].rgbtGreen;
                greenBlur += image[i][j+1].rgbtGreen;
                greenBlur += image[i+1][j].rgbtGreen;
                greenBlur += image[i+1][j+1].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 6);

                blueBlur += image[i-1][j].rgbtBlue;
                blueBlur += image[i-1][j+1].rgbtBlue;
                blueBlur += image[i][j+1].rgbtBlue;
                blueBlur += image[i+1][j].rgbtBlue;
                blueBlur += image[i+1][j+1].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 6);


            }
            // Right side
            else if (j == (width -1) && (i > 0 && i < height - 1))
            {
                redBlur += image[i-1][j].rgbtRed;
                redBlur += image[i-1][j-1].rgbtRed;
                redBlur += image[i][j-1].rgbtRed;
                redBlur += image[i+1][j-1].rgbtRed;
                redBlur += image[i+1][j].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 6);

                greenBlur += image[i-1][j].rgbtGreen;
                greenBlur += image[i-1][j-1].rgbtGreen;
                greenBlur += image[i][j-1].rgbtGreen;
                greenBlur += image[i+1][j-1].rgbtGreen;
                greenBlur += image[i+1][j].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 6);

                blueBlur += image[i-1][j].rgbtBlue;
                blueBlur += image[i-1][j-1].rgbtBlue;
                blueBlur += image[i][j-1].rgbtBlue;
                blueBlur += image[i+1][j-1].rgbtBlue;
                blueBlur += image[i+1][j].rgbtBlue;

                blur[i][j].rgbtGreen =  round(blueBlur / (float) 6);


            }
            // Top row of image
            else if (i == 0 && (j > 0 && j < width - 1))
            {
                redBlur += image[i][j+1].rgbtRed;
                redBlur += image[i+1][j-1].rgbtRed;
                redBlur += image[i][j-1].rgbtRed;
                redBlur += image[i+1][j+1].rgbtRed;
                redBlur += image[i+1][j].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 6);

                greenBlur += image[i][j+1].rgbtGreen;
                greenBlur += image[i+1][j-1].rgbtGreen;
                greenBlur += image[i][j-1].rgbtGreen;
                greenBlur += image[i+1][j+1].rgbtGreen;
                greenBlur += image[i+1][j].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 6);

                blueBlur += image[i][j+1].rgbtBlue;
                blueBlur += image[i+1][j-1].rgbtBlue;
                blueBlur += image[i][j-1].rgbtBlue;
                blueBlur += image[i+1][j+1].rgbtBlue;
                blueBlur += image[i+1][j].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 6);

            }
            // Bottom row of image
            else if (i == height -1 && (j > 0 && j < width - 1))
            {
                redBlur += image[i][j-1].rgbtRed;
                redBlur += image[i][j+1].rgbtRed;
                redBlur += image[i-1][j].rgbtRed;
                redBlur += image[i-1][j+1].rgbtRed;
                redBlur += image[i-1][j-1].rgbtRed;

                blur[i][j].rgbtRed =  round(redBlur / (float) 6);

                greenBlur += image[i][j-1].rgbtGreen;
                greenBlur += image[i][j+1].rgbtGreen;
                greenBlur += image[i-1][j].rgbtGreen;
                greenBlur += image[i-1][j+1].rgbtGreen;
                greenBlur += image[i-1][j-1].rgbtGreen;

                blur[i][j].rgbtGreen =  round(greenBlur / (float) 6);

                blueBlur += image[i][j-1].rgbtBlue;
                blueBlur += image[i][j+1].rgbtBlue;
                blueBlur += image[i-1][j].rgbtBlue;
                blueBlur += image[i-1][j+1].rgbtBlue;
                blueBlur += image[i-1][j-1].rgbtBlue;

                blur[i][j].rgbtBlue =  round(blueBlur / (float) 6);


            }
            // Middle
            else
            {
            redBlur += image[i][j-1].rgbtRed;
            redBlur += image[i][j+1].rgbtRed;
            redBlur += image[i-1][j].rgbtRed;
            redBlur += image[i+1][j].rgbtRed;
            redBlur += image[i+1][j-1].rgbtRed;
            redBlur += image[i-1][j-1].rgbtRed;
            redBlur += image[i-1][j+1].rgbtRed;
            redBlur += image[i+1][j+1].rgbtRed;

            blur[i][j].rgbtRed = round(redBlur / (float) 9);

            blueBlur += image[i][j-1].rgbtBlue;
            blueBlur += image[i][j+1].rgbtBlue;
            blueBlur += image[i-1][j].rgbtBlue;
            blueBlur += image[i+1][j].rgbtBlue;
            blueBlur += image[i+1][j-1].rgbtBlue;
            blueBlur += image[i-1][j-1].rgbtBlue;
            blueBlur += image[i-1][j+1].rgbtBlue;
            blueBlur += image[i+1][j+1].rgbtBlue;

            blur[i][j].rgbtBlue =  round(blueBlur / (float) 9);

            greenBlur += image[i][j-1].rgbtGreen;
            greenBlur += image[i][j+1].rgbtGreen;
            greenBlur += image[i-1][j].rgbtGreen;
            greenBlur += image[i+1][j].rgbtGreen;
            greenBlur += image[i+1][j-1].rgbtGreen;
            greenBlur += image[i-1][j-1].rgbtGreen;
            greenBlur += image[i-1][j+1].rgbtGreen;
            greenBlur += image[i+1][j+1].rgbtGreen;

            blur[i][j].rgbtGreen =  round(greenBlur / (float) 9);

            image[i][j].rgbtRed = blur[i][j].rgbtRed;
            image[i][j].rgbtGreen = blur[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blur[i][j].rgbtBlue;

            }

         }

     }

    return;
}
