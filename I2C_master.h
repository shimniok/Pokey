#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#define I2C_READ 0x01
#define I2C_WRITE 0x00
#define I2C_ACK 0x01
#define I2C_NACK 0x00

void I2C_init(void);
uint8_t I2C_start(const uint8_t address, const uint8_t read);
uint8_t I2C_write(const uint8_t data);
uint8_t I2C_read(const uint8_t ack);
void I2C_stop(void);

#endif // I2C_MASTER_H
