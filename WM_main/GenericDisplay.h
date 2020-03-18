#ifndef _GENERICDISPLAY_h
#define _GENERICDISPLAY_h



class GenericDisplay()
{
	public:
		virtual bool init_b() = 0;
		virtual bool DisplayString_b();
		virtual bool ClearScreen_b();
		virtual bool AutoScroll_b();
		virtual bool AutoScroll_b();
		virtual bool ChangeFontSize_b();
};


#endif