# Synchronization_ARM
Synchronization technique in ARM processors using Exclusive Instructions and bit fields.

I have created a simple API for synchronization, to be used on ARM Processors and others(if instructions available).

Main motive of API is to use less memory and have more functionalities for synchronization. I have used Bit-Field and Exclusive Laod-Store instructions to achieve so..


Usage of API is as follows:
- Check test application in test/src for reference

- Can add more data fields in structure according to usage and your design

- Tip:  Allocate the variable in such a way that it takes 1 byte of memory in memory space!
	Because the structure variable size is 1 byte, but when stack is created in memory space then it might take upto 4 bytes (on 32-bit) because of padding.
	Do variable allocation in such a way that it comes as single byte.

	void some_function( void )
	{
		unsigned short some_var_1;
		unsigned char some_var_2;
		sync_mutex_t synch_mutex = {.byte = 0};

		/* Processing */
	}

- Can be used for opeeation synchronization, exclusive data access etc..
