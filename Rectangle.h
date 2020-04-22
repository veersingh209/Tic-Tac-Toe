#ifndef Rectangle_h
#define Rectangle_h

//enum to store diffrent shapes
enum shape{empty, circle, xcross};

//struct to hold all rectangle variables
struct Rectangle {
    float xCoordinate;
    float yCoordinate;
    float width;
    float hight;
    bool isOccupied = false;
    //Shape object to hold is O, X or empty
    shape shape;
    
    //Default Constructor
    Rectangle();
    
    //Constructor
    Rectangle(float xCoordinate, float yCoordinate, float width, float hight);
    
    bool contains(float mx, float my);
    
    void draw();
};
#endif /* Rectangle_h */
