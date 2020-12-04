#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen  + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
}
// Caption of the sepia value
int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int originalRed = pixel.rgbtRed;
            int originalBlue = pixel.rgbtBlue;
            int originalGreen = pixel.rgbtGreen;
            image[i][j].rgbtRed = cap(round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
            image[i][j].rgbtGreen = cap(round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
            image[i][j].rgbtBlue = cap(round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));
        }
    }
}
// Swap the pixels
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

// Valid pixels
bool is_valid_pixel(int i, int j, int height, int width)
{
    return  i >= 0 && i < height && j >= 0 && j < width;
}


// Get Blurred pixels
RGBTRIPLE get_blurred_pixels(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int redvalue, bluevalue, greenvalue;
    redvalue = bluevalue = greenvalue = 0;
    int num_of_valid_Pixel = 0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = i + di;
            int new_j = j + dj;
            //)
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                num_of_valid_Pixel++;
                redvalue += image[new_i][new_j].rgbtRed;
                bluevalue += image[new_i][new_j].rgbtBlue;
                greenvalue += image[new_i][new_j].rgbtGreen;
            }
        }
    }
    RGBTRIPLE blurred_pixels;
    blurred_pixels.rgbtRed = round((float) redvalue / num_of_valid_Pixel);
    blurred_pixels.rgbtGreen = round((float) greenvalue / num_of_valid_Pixel);
    blurred_pixels.rgbtBlue = round((float) bluevalue / num_of_valid_Pixel);
    return blurred_pixels;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = get_blurred_pixels(i, j, height, width, image);
        }
    }

    // Copy the new image back into the old image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}

// Cap function
int cap_function(int value)
{
    return value < 255 ? value : 255;
}

// Get pixels of the edges
RGBTRIPLE get_edged_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int redvalueX, greenvalueX, bluevalueX, redvalueY, greenvalueY, bluevalueY;
    redvalueX = greenvalueX = bluevalueX = redvalueY = greenvalueY = bluevalueY = 0;
    // Solbon algorithem for every pixel
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (is_valid_pixel(i + di, j + dj, height, width))
            {
                // Compute GX value
                int weightx = Gx[di + 1][dj + 1];
                redvalueX += weightx * image[i + di][j + dj].rgbtRed;
                greenvalueX += weightx * image[i + di][j + dj].rgbtGreen;
                bluevalueX += weightx * image[i + di][j + dj].rgbtBlue;

                // Compute GY value
                // Getting the Gy matrix by reversing the order
                int weightY = Gx[dj + 1][di + 1];
                redvalueY += weightY * image[i + di][j + dj].rgbtRed;
                greenvalueY += weightY * image[i + di][j + dj].rgbtGreen;
                bluevalueY += weightY * image[i + di][j + dj].rgbtBlue;
            }
        }
    }
    // Calculate square root of Gx2 + Gy2 for each color ecodinr to the formular
    // Round to nearest integer and cap at 255
    RGBTRIPLE pixel;
    pixel.rgbtRed = cap_function(round(sqrt(redvalueX * redvalueX + redvalueY * redvalueY)));
    pixel.rgbtGreen = cap_function(round(sqrt(greenvalueX * greenvalueX + greenvalueY * greenvalueY)));
    pixel.rgbtBlue = cap_function(round(sqrt(bluevalueX * bluevalueX + bluevalueY * bluevalueY)));
    return pixel;
}
// Edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = get_edged_pixel(i, j, height, width, image);
        }
    }
    // Mutate the original image to a new one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}