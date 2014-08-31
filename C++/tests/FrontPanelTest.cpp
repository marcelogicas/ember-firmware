/* 
 * File:   FrontPanelTest.cpp
 * Author: Richard Greene
 * 
 * Used for manual testing of the front panel display.  
 * May be commented out when running automated tests.
 *
 * Created on Aug 31, 2014, 8:16:38 AM
 */

#include <stdlib.h>
#include <iostream>

#include <FrontPanel.h>
#include <Hardware.h>


void test1() {
    std::cout << "FrontPanelTest test 1" << std::endl;
       
    FrontPanel fp(UI_SLAVE_ADDRESS);
    
    PrinterStatus ps;
    ps._numLayers = 100;
    ps._currentLayer  = 30;;
    ps._estimatedSecondsRemaining = 4380;
    ps._errorCode = NoImageForLayer;
    ps._change = NoChange;
    ps._UISubState = NoUISubState;
    
    PrintEngineState pes =  PrinterOnState;  
    int iter = 1;
    // do forever
    for(;;)
    {
        ps._state = pes;  
        ps._errno = iter;
        
        ((ICallback*)&fp)->Callback(PrinterStatusUpdate, &ps);
        
        // read the front panel buttons while screen is being drawn
        // wait 200 ms first
        usleep(200000);
   
        unsigned char btns = fp.Read(BTN_STATUS) & 0xF;
        if(btns != 0)
            std::cout << "Buttons pressed: " << (int)btns << std::endl;
        
        pes = (PrintEngineState)(1 + (int) pes);
        if(pes >= MaxPrintEngineState)
        {
            pes = PrinterOnState;
            ++iter;
        }
    }
}


int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% FrontPanelTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (FrontPanelTest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (FrontPanelTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}
