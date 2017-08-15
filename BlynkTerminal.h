/****************************************************************************************
 * Blink terminal
 ****************************************************************************************/
BLYNK_WRITE(V10) //Virtual pin for terminal is set as v10 in app
{

  // Menu interaction
  if (String("calph7") == param.asStr()) 
  {
        command_string="99,CAL,7.00";
   
  }  
  else if (String("calph4") == param.asStr())  
  {
    command_string="99,CAL,4.00";
  } 
  else if (String("vars") == param.asStr())  
  {
    command_string="99,CAL,10.00"; 
  } 
  else if (String("help") == param.asStr())  
  {
    terminal.println("Current keywords:") ;
    terminal.println("calph7, calph4, calph10, help") ;
    terminal.println("calorp, statusph, statusorp") ;
    terminal.flush();  
  } 
  else if (String("calorp") == param.asStr())  
  {
    command_string="98,CAL,225";
  } 
  else if (String("statusph") == param.asStr())  
  {
    command_string="99,status";
  } 
  else if (String("statusorp") == param.asStr())  
  {
    command_string="98,status";
    terminal.flush(); 
    
    digitalWrite(relay_fridgePin, HIGH);
    
  }
  
  else 
  {
    // Send anything
    terminal.print("I'll try... ");
    //terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}
send_command();
