#pragma once
class BitMask
{
private:
	 int m_x, m_y, m_type;
	 unsigned char * m_mask;
public:
	BitMask(const String&);
	int getX() const;
	int getY() const;
	int getType() const;
	unsigned char * getMask() const;
	void loadMask(const String&);
	~BitMask(void);
};

