
class rtty{

  public:
    uint8_t baudrate;
    int pinnum;

    rtty(int pinnumber,uint8_t bauds){
        pinnum=pinnumber;
        baudrate=bauds;
    }

    void rtty_txstring (char * string)
    {
    
        /* Simple function to sent a char at a time to 
            ** rtty_txbyte function. 
            ** NB Each char is one byte (8 Bits)
            */
        
        char c;
        
        c = *string++;
        
        while ( c != '\0')
        {
            rtty_txbyte (c,2);
            c = *string++;
        }
    }
    
    
    void rtty_txbyte (char c, int stopbits=2)
    {
        /* Simple function to sent each bit of a char to 
            ** rtty_txbit function. 
            ** NB The bits are sent Least Significant Bit first
            **
            ** All chars should be preceded with a 0 and 
            ** proceded with a 1. 0 = Start bit; 1 = Stop bit
            **
            */
        
        int i;
        
        rtty_txbit (0); // Start bit
        
        // Send bits for for char LSB first	
        
        for (i=0;i<7;i++) // Change this here 7 or 8 for ASCII-7 / ASCII-8
        {
            if (c & 1) rtty_txbit(1); 
        
            else rtty_txbit(0);	
        
            c = c >> 1;
        
        }
        
        for (int i=0;i<stopbits;i++){
            rtty_txbit(1);
        }
    }
    
    void rtty_txbit (int bit)
    {
        if (bit)
        {
            // high
            digitalWrite(RADIOPIN, HIGH);
        }
        else
        {
            // low
            digitalWrite(RADIOPIN, LOW);
        
        }
        
        //int delaytime=1000000/baudrate;
        delayMicroseconds(3370); //todo:find out exactly how to calc this
    }
};

