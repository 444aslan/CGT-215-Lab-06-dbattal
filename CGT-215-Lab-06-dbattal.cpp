#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main() {
    string background = "images1/backgrounds/winter.png";
    string foreground = "images1/characters/yoda.png";

    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(background)) {
        cout << "Couldn't Load Image" << endl;
        exit(1);
    }
    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foreground)) {
        cout << "Couldn't Load Image" << endl;
        exit(1);
    }

    Image backgroundImage;
    backgroundImage = backgroundTex.copyToImage();
    Image foregroundImage;
    foregroundImage = foregroundTex.copyToImage();

    // taking green screen color from the corner of the foreground
    // setting the range for the color of the pixel. basically how close the pixel's color needs to be to the green screen's value to count
    Color screenColor = foregroundImage.getPixel(0, 0);
    int range = 50; 

    Vector2u sz = backgroundImage.getSize();
    for (int y = 0; y < sz.y; y++) {
        for (int x = 0; x < sz.x; x++) {
            Color fgC = foregroundImage.getPixel(x, y);

            // checking if theyre in the range
            // if they are, boom replace with background x,y coordinate pixel
            if (fgC.r > screenColor.r - range && fgC.r < screenColor.r + range &&
                fgC.g > screenColor.g - range && fgC.g < screenColor.g + range &&
                fgC.b > screenColor.b - range && fgC.b < screenColor.b + range) {
                Color bgC = backgroundImage.getPixel(x, y);
                foregroundImage.setPixel(x, y, bgC);
            }
        }
    }

    RenderWindow window(VideoMode(1024, 768), "Here's the output");
    Sprite sprite1;
    Texture tex1;
    tex1.loadFromImage(foregroundImage);
    sprite1.setTexture(tex1);
    window.clear();
    window.draw(sprite1);
    window.display();
    while (true);
}