#pragma once

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
          
class lcd_helper
{
	class data
	{
		private:
			
			String _value;
			uint8_t _pos;
			uint8_t _max_length;
			
		public:
		
			data();
			data(const String & value_, const uint8_t max_length);
			
			const data & operator= (const data & other);
			
			void increment();
			const char * c_str() const;
	};
	
	private:
	
		LiquidCrystal_I2C _lcd;
		uint8_t _cols;
		uint8_t _rows;
		data * _lines;
	
	public:
	
		lcd_helper(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);
		~lcd_helper();
		
		void set_text(uint8_t row, const String & text);
		void set_full_text(const String & text, bool wrap=true);
		void clear();
		
		void scroll();
		
		void display();
};
