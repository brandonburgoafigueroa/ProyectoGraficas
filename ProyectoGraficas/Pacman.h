

class Pacman
{
public:
	float x, y;
	double Angulo;
	double Velocidad;
	bool top, down, left, right;
public:
	
	Pacman(int x, int y)
	{
		this->x = x;
		this->y = y;
		Velocidad = 0.07;
		Angulo = 0;
		top = true;
		down = false;
		left = false;
		right = false;
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
		top = false;
		down = false;
		left = true;
		right = false;
	}
	else
		if (nangle == 0)
		{
			top = false;
			down = false;
			left = false;
			right = true;

		}
		else
			if (nangle == 90)
			{
				top = true;
				down = false;
				left = false;
				right = false;

			}
			else
				if (nangle == 270)
				{
					top = false;
					down = true;
					left = false;
					right = false;
				}
}
	void PadAndMove(int a)
	{
		Angulo = a;
	}
	void Move()
	{
		int xa, ya;
		if (top)
		{
			ya=1;
			xa = 0;
		}
		if (down)
		{
			ya = -1;
			xa = 0;
		}
		if (left)
		{
			ya = 0;
			xa = -1;
		}
		if (right)
		{
			ya = 0;
			xa = 1;
		}
		x += Velocidad * xa;
		y += Velocidad * ya;
	}

};
