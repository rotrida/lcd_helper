#include "lcd_helper.h"

lcd_helper::data::data():
	_pos(0),
	_max_length(0)
{	
}

const lcd_helper::data & lcd_helper::data::operator=(const lcd_helper::data & other)
{
	_value = other._value;
	_pos = other._pos;
	_max_length = other._max_length;
	
	return *this;
}

lcd_helper::data::data(const String & value, const uint8_t max_length):
	_value(value),
	_pos(0),
	_max_length(max_length)
{
}

void lcd_helper::data::increment()
{
	if(_value.length() <= _max_length)
		return;
		
	_pos++;
	
	if(_pos >= _max_length)
		_pos = 0;
}

const char * lcd_helper::data::c_str() const
{
	return &(_value.c_str()[_pos]);
}

lcd_helper::lcd_helper(uint8_t addr, uint8_t cols, uint8_t rows):
	_lcd(addr, cols, rows),
	_cols(cols),
	_rows(rows)
{
	_lines = new data[_rows];
	_lcd.begin();
}

lcd_helper::~lcd_helper()
{
	if(_lines)
		delete []_lines;
}

void lcd_helper::set_text(uint8_t row, const String & text)
{
	_lines[row] = data(text, _cols);
}

void lcd_helper::set_full_text(const String & text, bool wrap)
{
	uint8_t index = 0;
	
	for(uint8_t row = 0; row < _rows; row++)
	{
		const uint8_t remaining_length = text.length() - index;
		const auto copy_size = (wrap ? min(_cols, remaining_length) : remaining_length);
		
		if(copy_size > 0 && (row == 0 || wrap))
		{
			_lines[row] = data(text.substring(index, index + copy_size), _cols);
			index += copy_size;
		}
		else
			_lines[row] = data(String(), _cols);
	}	
}

void lcd_helper::clear()
{
	for(uint8_t row = 0; row < _rows; row++)
	{
		_lines[row] = data(String(), _cols);
	}	
}
		
void lcd_helper::scroll()
{
	for(uint8_t row = 0; row < _rows; row++)
	{
		_lines[row].increment();
	}
}

void lcd_helper::display()
{
	_lcd.clear();
    _lcd.home();
    
	
	for(uint8_t row = 0; row < _rows; row++)
	{
		_lcd.setCursor(0,row);
		_lcd.noCursor();
		_lcd.print(_lines[row].c_str());
	}
}
