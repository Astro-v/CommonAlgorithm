struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}
  
  Point(const Point& other): x{other.x}, y{other.y} {}
  
  Point(const Point* other): x{other->x}, y{other->y} {}
  
  Point(const int x, const int y) : x{x}, y{y} {}
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    return Line(new Point(start), new Point(end));
  }
};