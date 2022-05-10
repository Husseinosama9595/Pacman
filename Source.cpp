#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;
using namespace sf;
struct Ghosts
{
    bool PacCollision;
    bool hasFreeChoice;
    bool OccupiedSquares[4] = { true,true,true,true };

}G1, G2, G3, G4;
void CheckSquares();
void eatingcherry();
void eatingpoints();
bool gameover();

Ghosts GhostStorage[] = { G1,G2,G3,G4 };
Sprite Ghost[4];
Sprite pacman;
Sprite point;
Sound EatingSound;
string rec[22] = {
        " ################### ",
        " #C.......#.......C# ",
        " #.##.###.#.###.##.# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.### # ###.#### ",
        "    #.#...a...#.#    ",
        " ####.#.##=## #.#### ",
        " #......#bcd#..C...# ",
        " ####.#.#####.#.#### ",
        "    #.#.......#.#    ",
        " ####.# ##### #.#### ",
        " #...C....#........# ",
        " #.##.###.#.###.##.# ",
        " #..#.....P.....#..# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### ",
        "                     "
};
//Array = {Right,Left,Up,Down}
int tilesize = 32;
float movespeed = 64 / tilesize;
bool walking;
int OppositeMovement[4] = {};
int score = 0;
Text text;


//Checks for squares arround the ghosts
void CheckSquares()
{
    for (int l = 0; l < 4; l++)
    {


        for (int k = 0; k < 4; k++)
        {
            if (k == 0)
            {
                int j = (Ghost[l].getPosition().x + 32) / 32, i = Ghost[l].getPosition().y / 32;

                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }

            }
            if (k == 1)
            {
                int j = (Ghost[l].getPosition().x - 32) / 32, i = Ghost[l].getPosition().y / 32;

                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }
            if (k == 2)
            {
                int j = Ghost[l].getPosition().x / 32, i = (Ghost[l].getPosition().y - 32) / 32;
                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }
            if (k == 3)
            {
                int j = Ghost[l].getPosition().x / 32, i = (Ghost[l].getPosition().y + 32) / 32;
                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }


        }
    }
}
//pacman wins sound function

void eatingcherry() {
    int j = pacman.getPosition().x / 32, i = (pacman.getPosition().y) / 32;
    if (rec[i][j] == 'C')
    {
        rec[i][j] = ' ';
        SoundBuffer eatingcherry;
        eatingcherry.loadFromFile("pacman_eatfruit.wav");
        Sound Eatingcherry;
        Eatingcherry.setBuffer(eatingcherry);
        score+=100;
        text.setString("Score: " + to_string(score));

        Eatingcherry.play();
    }
}



void eatingpoints() {
    int j = pacman.getPosition().x / 32, i = (pacman.getPosition().y) / 32;
    if (rec[i][j] == '.')
    {
        rec[i][j] = ' ';
        SoundBuffer eatingSound;
        eatingSound.loadFromFile("pacman_chomp.wav");
        Sound EatingSound;
        EatingSound.setBuffer(eatingSound);
        score++;
        text.setString("Score: " + to_string(score));
         EatingSound.play();
    }
}

bool gameover() {
    bool PacmanDead = false;
    for (int Ggg = 0; Ggg < 4; Ggg++) {
        if (pacman.getPosition().x == Ghost[Ggg].getPosition().x && pacman.getPosition().y == Ghost[Ggg].getPosition().y) {
            PacmanDead = true;
        }
    }
    return PacmanDead;
}







//pacman wins sound function

//pacman dying sound function

void main()
{

    //window
    RenderWindow window(VideoMode(672, 704), "PAC MAN");
    window.setFramerateLimit(30);

    //Sound
    SoundBuffer beginning;
    beginning.loadFromFile("pacman_beginning.wav");
    Sound Beginning;
    Beginning.setBuffer(beginning);

    SoundBuffer eatingSound;
    eatingSound.loadFromFile("pacman_chomp.wav");
    Sound EatingSound;
    EatingSound.setBuffer(eatingSound);


    SoundBuffer death;
    death.loadFromFile("pacman_death.wav");
    Sound Death;
    Death.setBuffer(death);

    SoundBuffer winningsound;
    winningsound.loadFromFile("win.wav");
    Sound Winningsound;
    Winningsound.setBuffer(winningsound);

    //
    bool rightButton = false, leftButton = false, upButton = false, downButton = false;
    //
    int xvelocity = 0, yvelocity = 0;









    //rectangles size
    RectangleShape Rect;
    Rect.setSize(Vector2f(32, 32));

    //textures
    Texture pac;
    Texture ghost;
    Texture menu;
    Texture background;
    Texture Point;
    Texture cherry;
    Texture win;
    win.loadFromFile("winningscreen.png");
    cherry.loadFromFile("pacman cherry.jpg");
    menu.loadFromFile("main menu.jpeg");
    pac.loadFromFile("pacman sprite.jpeg");
    ghost.loadFromFile("ghost sprite.jpeg");
    Point.loadFromFile("point.jpeg");
    background.loadFromFile("background1.jpg");
    int counter = 0;



    //Sprites

    for (int i = 0; i < 4; i++) {
        Ghost[i].setTexture(ghost);
    }
    //Ghost[0].setColor(Color::Red);
    Ghost[0].setPosition(2 * 10 * 16, 2 * 7 * 16);
    //Ghost[1].setColor(Color::Blue);
    Ghost[1].setPosition(2 * 9 * 16, 2 * 9 * 16);
    //Ghost[2].setColor(Color::Green);
    Ghost[2].setPosition(2 * 10 * 16, 2 * 9 * 16);
    //Ghost[3].setColor(Color::Magenta);
    Ghost[3].setPosition(2 * 11 * 16, 2 * 9 * 16);
    pacman.setTexture(pac);
    //pacman.setColor(Color::Yellow);
    pacman.setPosition(2 * 10 * 16, 2 * 15 * 16);
    Rect.setFillColor(Color::Blue);
    Sprite Menu;
    Menu.setTexture(menu);
    Sprite Background;
    Background.setTexture(background);

    Sprite Cherry;
    Cherry.setTexture(cherry);

    Sprite point;

    point.setTexture(Point);


    Sprite winningscreen;
    winningscreen.setTexture(win);


    //Scales
    Cherry.setScale(0.0763888888888889, 0.0709459459459459);
    Menu.setScale(1.68, 2.346);
    Background.setScale(0.4666666666666667, 0.7822222222222222);
    
    pacman.setScale(1.5, 1.5);
    winningscreen.setScale(0.2625, 0.44);
    point.setScale(0.75, 0.75);
    for (int i = 0; i < 4; i++) {
        Ghost[i].setScale(1.523809523809524, 1.560975609756098);

    }
    bool intialmovement = true;

    //animation
    pacman.setTextureRect(IntRect(4, 6, 12, 12));
    Ghost[0].setTextureRect(IntRect(0, 0, 64, 64));
    Ghost[1].setTextureRect(IntRect(0, 20.5, 21, 20.5));
    Ghost[2].setTextureRect(IntRect(0, 41, 21, 20.5));
    Ghost[3].setTextureRect(IntRect(0, 61.5, 21, 20.5));
    int pacanimation = 0;
    int pacy = 0;
    int ghostanmi = 0;


    Font font;
    font.loadFromFile("Cabaret Display Italic.ttf");

    text.setFont(font);
    text.setString("score: " + to_string(score));
    text.setFillColor(Color::Green);
    text.setPosition(32, 8);
    text.setCharacterSize(16);
    text.setString("Score: " + to_string(score));
        
    //Music Playing
    Beginning.play();


    //Collision
    FloatRect nextPos;


    //Gameloop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();


            CheckSquares();
            //CheckSquares Function Beta Test
            /* for (int v = 0; v < 4; v++)
             {


                 for (int n = 0; n < 4; n++)
                 {
                     if (GhostStorage[v].OccupiedSquares[n] == true)
                     {
                         cout << 't';
                     }
                     else
                     {
                         cout << 'f';
                     }
                 }
                 cout << v << endl;
             }*/
            walking = false;


            int xcurr, leftnext, rightnext, ycurr, upnext, downnext;
            bool canMoveUp = true, canMoveDown = true, canMoveRight = true, canMoveLeft = true;
            leftnext = (pacman.getPosition().x - 32) / 32;
            xcurr = (pacman.getPosition().x) / 32;
            rightnext = (pacman.getPosition().x + 32) / 32;
            upnext = (pacman.getPosition().y - 32) / 32;
            ycurr = (pacman.getPosition().y) / 32;
            downnext = (pacman.getPosition().y + 32) / 32;
            if (rec[ycurr][leftnext] == '#')
            {
                canMoveLeft = false;
            }
            if (rec[ycurr][rightnext] == '#')
            {
                canMoveRight = false;
            }
            if (rec[upnext][xcurr] == '#')
            {
                canMoveUp = false;
            }
            if (rec[downnext][xcurr] == '#')
            {
                canMoveDown = false;
            }
            //cout << "Left Pos " << leftnext << endl << "Right Pos" << rightnext << endl << "Up Pos" << upnext << endl << "Down Pos " << downnext << endl;
            //cout << "Left " << canMoveLeft << endl << "Right " << canMoveRight << endl << "Up " << canMoveUp << endl << "Down " << canMoveDown << endl <<"endddddd\n";
            if ((Keyboard::isKeyPressed(Keyboard::A)) && canMoveLeft == true) {



                pacman.move(-16, 0);





                pacanimation++;
                pacy = 0;
                ghostanmi = 5;

            }

            else if ((Keyboard::isKeyPressed(Keyboard::D)) && canMoveRight == true) {




                pacman.move(16, 0);



                pacman.setOrigin(0, 0);

                pacanimation++;
                ghostanmi = 7;
                pacy = 1;

            }
            else  if ((Keyboard::isKeyPressed(Keyboard::W)) && canMoveUp == true) {

                pacman.move(0, -16);


                pacanimation++;
                ghostanmi = 1;
                pacy = 2;
            }
            else  if ((Keyboard::isKeyPressed(Keyboard::S)) && canMoveDown == true) {

                pacman.move(0, 16);


                pacanimation++;
                ghostanmi = 3;
                pacy = 3;
            }



        }

        int xpos = pacman.getPosition().x;
        int ypos = pacman.getPosition().y;
        int remx = xpos % 32;
        int remy = ypos % 32;
        if (remx != 0 || remy != 0)
            pacman.setPosition(xpos - remx, ypos - remy);

        //Pacman Death
        if (gameover() == true)
        {
           
            counter = 2;


        }
        //Ghost Movement
        int GhostEmptySpace[4];
        int emptycounter = 0;
        for (int ghos = 0; ghos < 4; ghos++)
        {


            for (int Sqr = 0; Sqr < 4; Sqr++)
            {
                if (GhostStorage[ghos].OccupiedSquares[Sqr] == false)
                {
                    emptycounter++;
                }

            }
            GhostEmptySpace[ghos] = emptycounter;
        }
        int intialPosX = pacman.getPosition().x;
        int intialPosY = pacman.getPosition().y;

        if ((intialPosX == 288 || intialPosX == 352) && intialPosY == 480 && intialmovement == true)
        {
            for (int ds = 0; ds < 3; ds++)
            {
                Ghost[0].move(-32, 0);
                OppositeMovement[0] = 0;
            }

            Ghost[1].move(32, 0);
            Ghost[1].move(0, -32);
            Ghost[1].move(0, -32);
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[1].move(-32, 0);
                OppositeMovement[1] = 0;
            }

            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[2].move(0, -32);
            }
            for (int ds = 0; ds < 3; ds++)
            {
                Ghost[2].move(32, 0);
                OppositeMovement[2] = 1;
            }
            Ghost[3].move(-32, 0);
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[3].move(0, -32);
            }
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[3].move(32, 0);
                OppositeMovement[3] = 1;
            }

            intialmovement = false;
        }
        if (intialmovement == false)
        {
            rec[8][10] = '#';
            for (int G = 0; G < 4; G++)
            {
                if (emptycounter > 2 || emptycounter == 1)
                {
                    int Const = 0;
                    Const = 1 + rand() % 4;
                    switch (Const)
                    {
                    case 1:
                        if (GhostStorage[G].OccupiedSquares[0] == false)
                        {
                            Ghost[G].move(32, 0);

                            OppositeMovement[G] = 1;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '1' << endl;
                        break;
                    case 2:
                        if (GhostStorage[G].OccupiedSquares[1] == false)
                        {
                            Ghost[G].move(-32, 0);

                            OppositeMovement[G] = 0;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '2' << endl;
                        break;
                    case 3:
                        if (GhostStorage[G].OccupiedSquares[2] == false)
                        {
                            Ghost[G].move(0, -32);

                            OppositeMovement[G] = 3;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '3' << endl;
                        break;
                    case 4:
                        if (GhostStorage[G].OccupiedSquares[3] == false)
                        {
                            Ghost[G].move(0, 32);

                            OppositeMovement[G] = 2;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '4' << endl;
                        break;
                    default:
                        break;
                    }

                }
                else
                {
                    for (int Sqr = 0; Sqr < 4; Sqr++)
                    {
                       // cout << G << " , " << OppositeMovement[G] << " , " << Sqr << endl;
                        if (GhostStorage[G].OccupiedSquares[Sqr] == false && Sqr != OppositeMovement[G])
                        {

                            switch (Sqr)
                            {
                            case 0:
                                Ghost[G].move(32, 0);
                                OppositeMovement[G] = 1;
                                break;
                            case 1:
                                Ghost[G].move(-32, 0);
                                OppositeMovement[G] = 0;
                                break;
                            case 2:
                                Ghost[G].move(0, -32);
                                OppositeMovement[G] = 3;
                                break;
                            case 3:
                                Ghost[G].move(0, 32);
                                OppositeMovement[G] = 2;
                                break;
                            default:
                                break;
                            }

                        }


                    }


                }


            }
        }




        /*for (int d = 0; d < 4; d++)
        {
            cout << GhostEmptySpace[d] << ' ' << endl;
        }*/




        //for menu:Start & Quit    WITH MOUSE
        if  (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mouseposition = Mouse::getPosition(window);
            if (mouseposition.x > 949.5 && mouseposition.x < 1579.5 && mouseposition.y>213.2 && mouseposition.y < 561.6) {
                window.close();
            }
            else if (mouseposition.x > 225 && mouseposition.x < 864 && mouseposition.y>213.2 && mouseposition.y < 561.6) {
                counter = 1;
            }
        }
        //game over
        //gameover();

        //for eating sound && points invisible
        eatingcherry();
        eatingpoints();


        //for animation
        pacman.setTextureRect(IntRect(pacanimation * 21.3, pacy * 21.5, 21.3, 21.5));
        Ghost[0].setTextureRect(IntRect(ghostanmi * 21, 0, 21, 20.5));
        Ghost[1].setTextureRect(IntRect(ghostanmi * 21, 20.5, 21, 20.5));
        Ghost[2].setTextureRect(IntRect(ghostanmi * 21, 41, 21, 20.5));
        Ghost[3].setTextureRect(IntRect(ghostanmi * 21, 61.5, 21, 20.5));

        pacanimation %= 3;
        //

        if(score==572)
        {
            counter = 3;
        
        }
        window.clear();
        window.draw(Background);
        if (counter == 0) {
            window.draw(Menu);

        }
        else if (counter == 1) {
            //drawing rectangles
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 21; j++)
                {
                    if (rec[i][j] == '#')
                    {
                        window.draw(Rect);
                        Rect.setPosition(j * 32, i * 32);
                    }
                    else if (rec[i][j] == 'P')
                    {
                        window.draw(pacman);

                    }
                    else if (rec[i][j] == 'a')
                    {
                        window.draw(Ghost[0]);
                    }
                    else if (rec[i][j] == 'b')
                    {
                        window.draw(Ghost[1]);
                    }
                    else if (rec[i][j] == 'c')
                    {
                        window.draw(Ghost[2]);
                    }
                    else if (rec[i][j] == 'd')
                    {
                        window.draw(Ghost[3]);
                    }
                    else if (rec[i][j] == '.')
                    {
                        window.draw(point);
                        point.setPosition(2 * j * 16.5, 2 * i * 16.5);
                    }
                    else if (rec[i][j] == 'C')
                    {
                        window.draw(Cherry);
                        Cherry.setPosition(2 * j * 16.5, 2 * i * 16.5);

                    }
                }
                window.draw(text);
            }

        }
        else if (counter == 2)
        {
            Texture gameover;
            gameover.loadFromFile("Gameover.jpeg");
            Sprite Gameover;
            Gameover.setTexture(gameover);
            Gameover.setScale(0.6227988878591288, 1.066666666666667);
            Death.play();
            window.draw(Gameover);
            counter += 10;
            //counter = 5;
        }
        else if (counter == 3)
        {
         
            sleep(seconds(2));
            text.setFillColor(Color::Cyan);
            text.setPosition(300, 352);
            text.setCharacterSize(108);
            text.setString("score: " + to_string(score));
            Winningsound.play();
            window.draw(text);
            window.draw(winningscreen);
            counter++;

        }
        for (int Gg = 0; Gg < 4; Gg++)
        {
            GhostStorage[Gg].OccupiedSquares[0] = true;
            GhostStorage[Gg].OccupiedSquares[1] = true;
            GhostStorage[Gg].OccupiedSquares[2] = true;
            GhostStorage[Gg].OccupiedSquares[3] = true;
        }
     
        window.display();

    }


}