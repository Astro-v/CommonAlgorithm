#include <string>
using namespace std;

struct Renderer
{
  virtual string render_triangle() const = 0;
  virtual string render_square() const = 0;
};

struct VectorRenderer : Renderer
{
    string render_triangle() const override
    {
        return "Drawing Triangle as lines";
    }
    
    string render_square() const override
    {
        return "Drawing Square as lines";
    }
};

struct RasterRenderer : Renderer
{
    string render_triangle() const override
    {
        return "Drawing Triangle as pixels";
    }
    
    string render_square() const override
    {
        return "Drawing Square as pixels";
    }
};

struct Shape
{
    Renderer& renderer;
    string name;
    Shape(Renderer& renderer, string name) : renderer{renderer}, name{name}
    {
        
    }
};

struct Triangle : Shape
{
    Triangle(Renderer& renderer) : Shape{renderer, "Circle"}
    {
        
    }
    
    string str() const
    {
        return renderer.render_triangle();
    }
};

struct Square : Shape
{
    Square(Renderer& renderer) : Shape{renderer, "Square"}
    {
        
    }
    
    string str() const
    {
        return renderer.render_square();
    }
};