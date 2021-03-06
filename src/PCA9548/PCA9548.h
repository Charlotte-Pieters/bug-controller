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
 
#ifndef MBED_PCA9547_H
#define MBED_PCA9547_H
 
#include "mbed.h"
 
/** PCA9548 class
 *
 *  PCA9548: an I2C bus multiplexer control library
 *
 *  PCA9548 is an I2C multiplexer which enables to select 1:8 multiplexed I2C bus.
 *  The multiplexer is useful for deviding I2C bus to avoiding slave address conflict and separating capacitive loads.
 *
 *  For more informatioj about PCA9548:
 *    http://www.nxp.com/documents/data_sheet/PCA9548.pdf
 *
 *  Example:
 *  @code
 *  #include "mbed.h"
 *  #include "LM75B.h"
 *  #include "PCA9548.h"
 *
 *  PCA9548 mux( p28, p27, 0xE0 );
 *
 *  int main()
 *  {
 *      mux.select( 0 );
 *
 *      LM75B   tmp0( p28, p27 );   //  making instance after a branch of I2C bus (which is connecting the LM75B) enabled
 *
 *      while(1) {
 *          printf( "%.3f\r\n", tmp0.read() );
 *          wait( 1.0 );
 *      }
 *  }
 *  @endcode
 */
 
class PCA9548
{
public:
 
    /** Create a PCA9548 instance connected to specified I2C pins with specified address
     *
     * @param sda I2C-bus SDA pin
     * @param scl I2C-bus SCL pin
     * @param i2c_address I2C-bus address (default: 0xE0)
     */
    PCA9548( PinName sda, PinName scl, char i2c_address = 0xE0 );
 
    /** Create a PCA9546A instance connected to specified I2C pins with specified address
     *
     * @param &i2c_ I2C object (instance)
     * @param i2c_address I2C-bus address (default: 0xE0)
     */
    PCA9548( I2C &i2c_, char i2c_address = 0xE0 );
 
    /** Destructor of PCA9548
     */
    ~PCA9548();
 
    /** Channel select
     *
     *  Enable and select a channel
     *
     * @param channel channel number
     */
    void select( char channel );
 
    /** Disabling all channels
     *
     *  Disable all channels
     */
    void disable( void );
 
private:
    I2C     *i2c_p;
    I2C     &i2c;
    char    i2c_addr;
};
 
#endif  //  MBED_PCA9547_H
            