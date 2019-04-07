/**
 *  PCA9548 library
 *
 *  @author  Tedd OKANO
 *  @version 0.2
 *  @date    Feb-2015
 *
 *  PCA9548: an I2C bus multiplexer control library
 *
 *  PCA9548 is an I2C multiplexer which enables to select 1:8 multiplexed I2C bus.
 *  The multiplexer is useful for deviding I2C bus to avoiding slave address conflict and separating capacitive loads.
 *
 *  For more information about PCA9548:
 *    http://www.nxp.com/documents/data_sheet/PCA9548.pdf
 *
 */
 
#include "PCA9548.h"
 
PCA9548::PCA9548( PinName sda, PinName scl, char i2c_address )
    : i2c_p( new I2C( sda, scl ) ), i2c( *i2c_p ), i2c_addr( i2c_address )
{
    //  do nothing.
    //  leave it in default state.
}
 
PCA9548::PCA9548( I2C &i2c_, char i2c_address )
    : i2c_p( NULL ), i2c( i2c_ ), i2c_addr( i2c_address )
{
    //  do nothing.
    //  leave it in default state.
}
 
PCA9548::~PCA9548()
{
    if ( NULL != i2c_p )
        delete  i2c_p;
}
 
void PCA9548::select( char channel )
{
    char data = 0x08 | channel;
    int result = i2c.write( i2c_addr, &data, 1 );
}
 
void PCA9548::disable( void )
{
    char data = 0x00;
    int result = i2c.write( i2c_addr, &data, 1 );
}