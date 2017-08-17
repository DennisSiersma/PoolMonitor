// USAGE:
//---------------------------------------------------------------------------------------------
// - Set all your EZO circuits to I2C before using this sketch.
//    - You can use the "tentacle-steup.ino" sketch to do so)
//    - Make sure each circuit has a unique I2C ID set 
// - Set host serial terminal to 9600 baud
//
// - To send a command, send the number of the i2c address, a colon and the command ending with a carriage return.
//
// - To issue a command, enter it directly to the console.
//
// 102:r<CR>
// 99:i<CR>
// 100:c<CR>
// 99:r<CR>
// 110:cal,mid,7.00<CR>
//
//---------------------------------------------------------------------------------------------

// EZO stamp code for PH and ORP
// do serial communication in a "asynchronous" way

void do_serial() {
  if (millis() >= next_serial_time) {                // is it time for the next serial communication?
    for (int i = 0; i < TOTAL_CIRCUITS; i++) {       // loop through all the sensors
      Serial.print(channel_names[i]);                // print channel name
      Serial.print(":\t");
      Serial.println(readings[i]);                    // print the actual reading
      //Serial.println(i);
      PH_val = readings[1];
      ORP_val = readings[0];
      drawEZO();
      Serial.println(PH_val + " " + ORP_val);
    }
    next_serial_time = millis() + send_readings_every;
  }
}


// take sensor readings in a "asynchronous" way
void do_sensor_readings() {
  if (request_pending) {                          // is a request pending?
    if (millis() >= next_reading_time) {          // is it time for the reading to be taken?
      receive_reading();                          // do the actual I2C communication
    }
  } else {                                        // no request is pending,
    channel = (channel + 1) % TOTAL_CIRCUITS;     // switch to the next channel (increase current channel by 1, and roll over if we're at the last channel using the % modulo operator)
    request_reading();                            // do the actual I2C communication
  }
}


// Request a reading from the current channel
void request_reading() {
  request_pending = true;
  Wire.beginTransmission(channel_ids[channel]); // call the circuit by its ID number.
  Wire.write('r');                    // request a reading by sending 'r'
  Wire.endTransmission();                   // end the I2C data transmission.
  next_reading_time = millis() + reading_delay; // calculate the next time to request a reading
}

void send_command() {
  request_pending = true;
  Wire.beginTransmission(channel_ids[channel]);  // call the circuit by its ID number.
  Wire.write(command_string);                               // request a reading by sending command
  Wire.endTransmission();                        // end the I2C data transmission.
  next_reading_time = millis() + reading_delay;  // calculate the next time to request a reading
  command_string='r';
}

// Receive data from the I2C bus
void receive_reading() {
  sensor_bytes_received = 0;                        // reset data counter
  memset(sensordata, 0, sizeof(sensordata));        // clear sensordata array;

  Wire.requestFrom(channel_ids[channel], 48, 1);    // call the circuit and request 48 bytes (this is more then we need).
  code = Wire.read();

  while (Wire.available()) {          // are there bytes to receive?
    in_char = Wire.read();            // receive a byte.

    if (in_char == 0) {               // if we see that we have been sent a null command.
      Wire.endTransmission();         // end the I2C data transmission.
      break;                          // exit the while loop, we're done here
    }
    else {
      sensordata[sensor_bytes_received] = in_char;  // load this byte into our array.
      sensor_bytes_received++;
    }
  }

  switch (code) {                       // switch case based on what the response code is.
    case 1:                             // decimal 1  means the command was successful.
      readings[channel] = sensordata;
      break;                              // exits the switch case.

    case 2:                             // decimal 2 means the command has failed.
      readings[channel] = "error: command failed";
      break;                              // exits the switch case.

    case 254:                           // decimal 254  means the command has not yet been finished calculating.
      readings[channel] = "reading not ready";
      break;                              // exits the switch case.

    case 255:                           // decimal 255 means there is no further data to send.
      readings[channel] = "error: no data";
      break;                              // exits the switch case.
  }
  request_pending = false;                  // set pending to false, so we can continue to the next sensor
}

/*void I2C_call() {               // function to parse and call I2C commands
  sensor_bytes_received = 0;                    // reset data counter
  memset(sensordata, 0, sizeof(sensordata));    // clear sensordata array;

  if (cmd[0] == 'c' || cmd[0] == 'r')time = 1400;
  else time = 300;                              //if a command has been sent to calibrate or take a reading we
  //wait 1400ms so that the circuit has time to take the reading.
  //if any other command has been sent we wait only 300ms.
  
  Wire.beginTransmission(channel);  // call the circuit by its ID number.
  Wire.write(cmd);            // transmit the command that was sent through the serial port.
  Wire.endTransmission();           // end the I2C data transmission.

  delay(time);

  code = 254;       // init code value

  while (code == 254) {                 // in case the command takes longer to process, we keep looping here until we get a success or an error

    Wire.requestFrom(channel, 48, 1);   // call the circuit and request 48 bytes (this is more then we need).
    code = Wire.read();

    while (Wire.available()) {          // are there bytes to receive.
      in_char = Wire.read();            // receive a byte.

      if (in_char == 0) {               // if we see that we have been sent a null command.
        Wire.endTransmission();         // end the I2C data transmission.
        break;                          // exit the while loop.
      }
      else {
        sensordata[sensor_bytes_received] = in_char;  // load this byte into our array.
        sensor_bytes_received++;
      }
    }


    switch (code) {                   // switch case based on what the response code is.
      case 1:                         // decimal 1.
        Serial.println("Success");    // means the command was successful.
        break;                          // exits the switch case.

      case 2:                         // decimal 2.
        Serial.println("< command failed");     // means the command has failed.
        break;                          // exits the switch case.

      case 254:                       // decimal 254.
        Serial.println("< command pending");    // means the command has not yet been finished calculating.
        delay(200);                     // we wait for 200ms and give the circuit some time to complete the command
        break;                          // exits the switch case.

      case 255:                       // decimal 255.
        Serial.println("No Data");    // means there is no further data to send.
        break;                          // exits the switch case.
    }

  }

  Serial.println(sensordata);         // print the data.
}
*/

