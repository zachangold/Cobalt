#ifndef InputH
#define InputH

class Window;

class Input
{
public:
	Input( Window& source );
	~Input( void );


private:
	Window& source;

};


#endif /* InputH */