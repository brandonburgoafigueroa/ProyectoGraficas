

class Pac
{
public:
	float x, y;
	double angle;
	double speed;
public:
	
	Pac(int x, int y)
	{
		this->x = x;
		this->y = y;
		speed = 0.09;
		angle = 0;
	}
	void Draw()
	{
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(x, y, 0.0);
		glutSolidSphere(2, 400, 400);
		glPopMatrix();
	}

void Turn(int nangle)
{
	if (nangle == 180)
	{
		PadAndMove(nangle);
	}
	else
		if (nangle == 0)
		{
			PadAndMove(nangle);

		}
		else
			if (nangle == 90)
			{
				PadAndMove(nangle);

			}
			else
				if (nangle == 270)
				{
					PadAndMove(nangle);
				}
}
	void PadAndMove(int a)
	{
		angle = a;
	}
	void Move()
	{
		x += speed * cos(M_PI / 180 * angle); // dodawany jakis staly interwal
		y += speed * sin(M_PI / 180 * angle);
	}

};
