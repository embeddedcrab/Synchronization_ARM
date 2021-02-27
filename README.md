# Synchronization_ARM
Synchronization technique in ARM processors using Exclusive Instructions and bit fields.

I have created a simple API for synchronization, to be used on ARM Processors and others(if instructions available).

Main motive of API is to use less memory and have more functionalities for synchronization in single data field. 
I have used Bit-Field and Exclusive Laod-Store instructions to achieve so..

---------------------------------------------------------------------------------------------------------------------

Usage of API is as follows:
- Check test application in test/src for reference

- Can add more data fields in structure according to usage and your design

- Can be used for operation synchronization, exclusive data access etc..

---------------------------------------------------------------------------------------------------------------------

Tip:  Allocate the variable in such a way that it takes 1 byte of memory in memory space!

void some_function( void )
{
	unsigned short some_var_1 = 0;
	unsigned char some_var_2 = 0;
	sync_mutex_t synch_mutex = {.byte = 0};
	
	/* Processing */
}





Explore it, you will definitely like it.
Happy to Help and Share 😊

Cheers!!
