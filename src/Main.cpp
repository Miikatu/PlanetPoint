#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <cmath>
#include <pthread.h>
#include <mutex>

using std::cout;
using std::endl;

/*
 * TODO:
 * modify world on click
*/

class Tile //Class for that tiles implement
{
    
public:
    int id;
    Tile(int newId);
    sf::Color getTypeColor(int id);
    void setId(int newId);
    sf::Vector2f position;
};

Tile::Tile(int newId){
    id = newId;
   
}

void Tile::setId(int newId){
   id=newId; 
}

sf::Color Tile::getTypeColor(int id){
    sf::Color color;
    switch(id)
    {
        case 0:
            color=sf::Color::Yellow;
            break;
        case 1:
            color=sf::Color::Green;
            break;
         case 2:
            color=sf::Color::Green;
            break;
        default:
            color=sf::Color::Red;
            break;
    }
    return color;
}

class World //Class for World info
{
    //- Maailma on kaunis ja hyvä elää sille, 
    //jolla on aikaa koodailuille -
    
public:
    World();
    int tileSizeX;
    int tileSizeY;
    int worldSizeX;
    int worldSizeY;
    
    void fill();
    void render(); 
    void printSize(std::vector<std::vector<Tile>>& grid);
    void handleClick(sf::Vector2i clickPosition);
    void drawGrid(sf::RenderWindow& window);
    
    sf::RenderWindow window;
    
    //Test items
    std::vector<std::string> testString{"Sammakko", " Hirvi", "Hiiri"};
    
    sf::RectangleShape base;
    std::vector<std::vector<Tile>> grid;
    std::vector<std::vector<Tile>> getGrid();
    std::vector<std::vector<Tile>> getLayer();
    
    
    
        
};

void World::drawGrid(sf::RenderWindow& window){
    float posX = 0.f;
    float posY = 0.f;
    for(std::vector<Tile> row : grid ){ 
       for(Tile tile : row){
           sf::RectangleShape shape;           
           shape.setSize(sf::Vector2f(tileSizeX,tileSizeY));
           shape.setPosition(tile.position);
           shape.setFillColor(tile.getTypeColor(tile.id));
           
           posX = posX + tileSizeX;
           window.draw(shape);
        }
        posY=posY+tileSizeY;
    }
}

World::World(){
    //intialize world size
    // TODO: set size from parameters
    //
    worldSizeX=1000;
    worldSizeY=1000;
    //Initialize base
    // TODO: set size from parameters
    //
    base.setFillColor(sf::Color::Yellow);
    base.setSize(sf::Vector2f((float)worldSizeX,(float)worldSizeY));
    //initialize tile size
    // TODO: set tile size from parameters
    //
    tileSizeX=10;
    tileSizeY=10;
}//World constructor

void World::fill(){
    //Add base layer
    //
    
    //Add first row to map
    //

    /* 
    std::vector<Tile> row;
   
    for(int j =0; j<worldSizeY;j++){
        for(int i = 0; i< worldSizeX;i++){ 
            Tile tile(1);            row.push_back(tile);
        } 
    }
    grid.push_back(row);*/
    
    //Add second row
    // 
    /*
    std::vector<Tile> row2;
    for(int i = 0; i< worldSizeX;i++){
        Tile tile(sf::Color::Green);
        tile.shape.setPosition(sf::Vector2f{(float)i*(float)tileSizeX,(float)tileSizeY*2});
        row2.push_back(tile);
    }
    
    grid.push_back(row2); */
    
    // TODO: fill the world with faster layer based method
    // About Method: Base color, each change in terrain adds a layer on top
    // 
    std::vector<Tile> apples;
    for(int i=0 ;i <100;i++){
        Tile apple(2);
        int randomX = rand()%1000-1;
        int randomY = rand()%1000-1;
        cout<<randomY<<"\n";
        
        apple.position.x=randomX-randomX%10;
        apple.position.y=randomY-randomY%10;
        
        //apple.setPosition(randomX*50,randomY*50); //Random coordinate       
        //apple.setFillColor(sf::Color::Blue);
        //apple.setSize(sf::Vector2f((float)tileSizeX,(float)tileSizeY));
        
        apples.emplace_back(apple);
    }
    grid.push_back(apples);
    
}
//TODO handle tile acces better'
//TODO change id of clicked tile
//handleClick sets tile's id when tile is clicked
void World::handleClick(sf::Vector2i clickPosition){
    
    //int indexX = clickPosition.x;
    //int indexY = clickPosition.y;
    
    int i{0},k{0};
    
    //Print index of clicked tile
    //cout<<"Handling clicked position[x,y]: ["<< clickPosition.x<<","<<clickPosition.y<<"]"<<"\n";
    printSize(grid);
    for(std::vector<Tile> row : grid){
       for(Tile tile : row){
           k++;
           std::ignore = tile;
           if(k==clickPosition.y){
                cout<<"Pointed Tile's id changed from "<< tile.id;
                if(tile.id == 0)
                    {
                        cout<<" to 1 \n";
                        tile.setId(1);
                        }
                else{
                    cout<<" to 0 \n";
                    tile.setId(0);
                }
                
            cout<< "Pointed Tile id = "<< tile.id<< "\n";
               
           }
       }
       i++;
   }
   
   cout<<"Rows: "<<i<<" Columns: "<<k;
    
    
    
    
}

void World::printSize(std::vector<std::vector<Tile>>& grid){
    //cout<<"row size: "<<row.size()<<"\n";
    cout<<"printing size "<< grid[0].size() <<"\n";
   for (std::vector<Tile> vt : grid){
       for(Tile t: vt ){
            cout<<"Item found"<<t.id<<"\n";
       }
   }
    
    
     
}
std::vector<std::vector<Tile>> World::getGrid(){

    return grid;
}
  
class Game 
{   
public:
    Game();
    void run();
    void directionOnKeyPressed(char input);
    void move(sf::Time deltaTime);
    void move();
    sf::Time deltaTime;
    World *world = new World();
    std::vector<std::vector<Tile>> grid;
    
private:
    sf::Vector2f tileSize{10.f,10.f};
    char input;
    int windowWidth{715};
    int windowHeight{715};
    sf::RenderWindow window;
    
    enum directionKey{ DOWN,UP,LEFT,RIGHT};
    struct Selection{
        sf::Vector2f clickPosition;
        sf::RectangleShape clickedTile;
        sf::Vector2i selectedTileIndex;
    };
    Selection selection;
    
    
    //Grid
    //
    std::forward_list<sf::RectangleShape> verticalLines;
    //std::list<sf::RectangleShape> verticalLines;
    std::list<sf::RectangleShape> horizontalLines;
    sf::RectangleShape border;
    //sf::Sprite background;
    sf::Texture texture;
    
    //Apple container
    //
    std::vector<sf::RectangleShape> apples;
    void eventListener();
    void render();
    void render(sf::Clock gameClock);
    void collisionCheck();
    void boundCheck();
    void handleClick(sf::Vector2i clickPosition, std::vector<std::vector<Tile>> newGrid);
};


//TODO handle tile acces better'
//TODO change id of clicked tile
//handleClick sets tile's id when tile is clicked

/* int tiler{0};
                    cout<<"print our Grid\n";
                        for(std::vector<Tile> v : grid){
                            for(Tile t : v){
                                std::ignore = t;
                                cout<<tiler<<"\n";
                                tiler++;
                            }
                    }*/
void Game::handleClick(sf::Vector2i clickPosition, std::vector<std::vector<Tile>> newGrid){
    
    //int indexX = clickPosition.x;
    //int indexY = clickPosition.y;
    
    int i{0},k{0};
    
    //Test world items
    world->base.setFillColor(sf::Color::Cyan);
    cout<<"World items ("<<world->testString.size()<<")\n";
    int testStringSize = world->testString.size();
    for(int index = 0; index < testStringSize; index++)
        cout<<world->testString[index]<<"\n";
    world->testString.pop_back();
    
    //Print index of clicked tile
    //cout<<"Handling clicked position[x,y]: ["<< clickPosition.x<<","<<clickPosition.y<<"]"<<"\n";
    //std::vector<std::vector<Tile>> grid;
    for(std::vector<Tile> row : newGrid){
       for(Tile tile : row){
           k++;
           std::ignore = tile;
           cout<<tile.id;
           if(k==clickPosition.y){
                cout<<"Tile id changed from "<< tile.id;

                if(tile.id == 0){
                    cout<<" to 1 \n";
                    tile.id=1;
                    newGrid.at(clickPosition.y).at(clickPosition.x)=tile;
                }
                else{
                    cout<<" to 0 \n";
                    tile.id=0;
                }
                
            cout<< "Clicked Tile id = "<< tile.id<< "\n";
               
           }
       }
       i++;
   }
   grid=newGrid;
   cout<<"Rows: "<<i<<" Columns: "<<k;
}

//Game Constructor, with initializer
//
Game::Game(): window(sf::VideoMode(windowWidth,windowHeight),"Devaan koululla"){
    std::cout<<"Construction done!"<< std::endl;
    //Window border
    //
    border.setSize(sf::Vector2f(windowWidth,windowHeight));
    border.setFillColor(sf::Color::Blue);
    border.setPosition(0,0);
    
    //Add lines to grid)
    sf::RectangleShape lineV(sf::Vector2f(5,windowHeight));
    for(int i{0};i<windowWidth;i+=55){
        lineV.setPosition(i,0);
        verticalLines.push_front(lineV);
    }
    sf::RectangleShape lineH(sf::Vector2f(windowWidth,5));
    for(int i{0};i<windowHeight;i+=55){
        lineH.setPosition(0,i);
        horizontalLines.push_front(lineH);
    }

    //Add background Texture
    
    //Create object of world
    //
    
    //Fill World Map with shapes
    //
    world->fill();
    grid=world->grid;
    
    cout<<"print our Grid\n";
    int tiles{0};
    for(std::vector<Tile> v : grid){
        for(Tile t : v){
            std::ignore = t;
            cout<<tiles<<"\n";
            tiles++;
        }
    }
    //Set selection tile Size
    //
    selection.clickedTile.setPosition(0,0);
    selection.clickedTile.setSize(sf::Vector2f(10.f,10.f));
    selection.clickedTile.setSize(sf::Vector2f(10.f,10.f));
    selection.clickedTile.setFillColor(sf::Color::Red);
    
    //Add apples to map
    //
    /*
    for(int i=0 ;i <100;i++){
        sf::RectangleShape apple;
        int randomX = rand()%10;
        int randomY = rand()%10;
        apple.setPosition(randomX*50,randomY*50); //Random coordinate       
        apple.setFillColor(sf::Color::Blue);
        apple.setSize(tileSize);
        apples.emplace_back(apple);
    }*/
    
}//Game Constructor ends

void Game::eventListener(){
    sf::Event event;
        //while pending events
        while (window.pollEvent(event)) 
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            
                case sf::Event::Resized:
                    windowHeight=window.getSize().y;
                    windowWidth=window.getSize().x;
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    selection.clickPosition.x=
                    sf::Mouse::getPosition(window).x
                        -((sf::Mouse::getPosition(window).x)%10);
                    selection.clickPosition.y=sf::Mouse::getPosition(window).y
                        -((sf::Mouse::getPosition(window).y)%10);
                    selection.selectedTileIndex.x=(int)selection.clickPosition.x/10;
                    selection.selectedTileIndex.y=(int)selection.clickPosition.y/10;
                    cout<<"Clicked on: ["
                        <<sf::Mouse::getPosition(window).x<<" , "
                        <<sf::Mouse::getPosition(window).y<<"] : "
                        <<"[["<<selection.clickPosition.x<<"]["
                        <<selection.clickPosition.y<<"]] : "
                        <<"[["<<selection.selectedTileIndex.x
                        <<"]["<<(int)selection.selectedTileIndex.y<<"]] \n";
                    selection.clickedTile.setPosition(selection.clickPosition);
                    world->handleClick(selection.selectedTileIndex);
                    
                    //TODO: handle ckickl without crash
                    //handleClick(selection.selectedTileIndex,grid);
                   
                    /*cout<<"id of clickedTile now is: "<<
                    grid.at(selection.selectedTileIndex.x)
                    .at(selection.selectedTileIndex.y).id<<"\n";*/
                    //grid[selection.selectedTileIndex.y][selection.selectedTileIndex.x].id=0;
                    break;
                }
                case sf::Event::TextEntered:
                    directionOnKeyPressed(
                        static_cast<char>(event.text.unicode));
                    break;
                    
                case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Escape)
                        window.close();
                    break;
                        
                default:
                    break;
            }
            
            if (event.type == sf::Event::Closed)
                window.close();

        }//Program exited
}//EventListener

void Game::directionOnKeyPressed(char input){
    switch(input)
    {
        case 'w':
            selection.clickedTile.move(0,-10);
            break;        
        case 'a':
            selection.clickedTile.move(-10,0);    
            break;
        case 's':
            selection.clickedTile.move(0,10);
            break;
        case 'd':
            selection.clickedTile.move(10,0);
            break;
    }
    cout<<"Moved to: "
        <<"[["<<selection.clickedTile.getPosition().x
        <<"]["<<selection.clickedTile.getPosition().y<<"]] : "
        <<"[["<<(int)selection.clickedTile.getPosition().x/10
        <<"]["<<(int)selection.clickedTile.getPosition().y/10<<"]] \n";
};//directionOnKeyPressed

//Game Render
//
void Game::render(){
    
    window.clear();
    window.draw(world->base);

    //Draw tiles
    //
        
   
    //std::vector<std::vector<Tile>> brig{world.getGrid()};
    
    //Print world size on each loop
    //cout<<"world grid size:" << world.grid.size()<<"\n";
    
    
    
    //Draw Grid
    /*
    for(std::vector<Tile> row : grid ){ 
       std::cout<<"row found"<<", its size is "<< row.size()<<"\n";
       for(Tile tile : row){

           sf::RectangleShape shape;           
           shape.setSize(sf::Vector2f(world->tileSizeX,world->tileSizeY));
           shape.setPosition(tile.position);
           shape.setFillColor(tile.getTypeColor(tile.id));
           
           posX = posX + world->tileSizeX;
           window.draw(shape);
        }
        posY=posY+world->tileSizeY;
    }*/
    
    world->drawGrid(window);
    
    //Draw grid
    //
    /*
    for(std::vector<Tile> row: world.grid){

        for(Tile tile : row){
            sf::RectangleShape item;
            item.setFillColor(tile.getTypeColor(tile.id));
            item.setPosition(tile.position);
            window.draw(item);
        }
    }*/
    //Draw Apples
    //Program exited
    /*
    std::for_each(apples.begin(),apples.end(),[&](auto& apple){
        window.draw(apple);
    });*/
    
    //Draw selection
    //
    window.draw(selection.clickedTile);
    
    window.display();
}//GameRender



void Game::run(){
    
    std::cout<<"Running game inside a Thread"<< std::endl;
    sf::Clock deltaClock;
    sf::Clock gameClock;
    
    int framesPerSecond{15};
    int skipTicks{125};
    sf::Int32 sleepTime{0};
    //bool game_is_running = true;
    //GameLoop
    //
    float nextGameTick= deltaClock.getElapsedTime().asMilliseconds();

    while(window.isOpen()){
       
        eventListener(); 
        gameClock.restart();
        render();
        
        nextGameTick+=skipTicks;
        sleepTime=nextGameTick-deltaClock.getElapsedTime().asMilliseconds();
        if(sleepTime>=0){
            //sleepTime;
            sf::sleep(sf::milliseconds(sleepTime));
            //sleep(sleepTime);
        }
        else {
            //myöhässä
        }
        // Calculate deltaTime
        //deltaTime = deltaClock.restart(); 
        
        framesPerSecond++;
    }
}


int main()
{   
    //Create instance of Game
    
    Game game;
    sf::Thread gameThread(&Game::run,&game);
    gameThread.launch();
    
    //Example of threading a class --> sf::Thread thread(&MyClass::func, &object);

    return 0;

}
