struct Square
{
  int side{ 0 };


  explicit Square(const int side)
    : side(side)
  {
  }
};

struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

struct SquareToRectangleAdapter : Rectangle
{
  int side;
    
  SquareToRectangleAdapter(const Square& square)
  {
    side = square.side;
  }
  
  int width() const override
  {
    return side;
  }
  
  int height() const override
  {
    return side;
  }
};