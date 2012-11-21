#pragma once
enum CollType{
	c_wall =0,
	c_none =255
};
class Bitmask
{
private:
	 int m_x, m_y, m_type;
	 unsigned char * m_mask;
	 Vector2 m_size;
public:
	Bitmask(const String&);
	int getX() const;
	int getY() const;
	int getType() const;
	CollType checkCollition(const Vector2&, const Vector2&) const;
	//void Bitmask::setSize(const Vector2& size);
	unsigned char * getMask() const;
	void loadMask(const String&);
	~Bitmask(void);
};

