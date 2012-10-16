//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


import ned.DatarateChannel;
simple Txc1
{
    gates:
        inout gate[];
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Tictoc1
{
    @display("bgb=510,322");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }

    submodules:

        S: Txc1 {
            @display("p=48,144");
        }
        A: Txc1 {
            @display("p=138,144");
        }
        B: Txc1 {
            @display("p=184,46");
        }
        C: Txc1 {
            @display("p=236,144");
        }
        X: Txc1 {
            @display("p=486,78");
        }
        E: Txc1 {
            @display("p=319,46");
        }
        H: Txc1 {
            @display("p=428,234");
        }

        F: Txc1 {
            @display("p=311,240");
        }
        G: Txc1 {
            @display("p=197,247");
        }
        I: Txc1 {
            @display("p=408,46");
        }
        J: Txc1 {
            @display("p=379,144");
        }
        L: Txc1 {
            @display("p=369,286");
        }
        K: Txc1 {
            @display("p=447,144");
        }
    connections:

        S.gate++ <--> Channel <--> A.gate++;
        A.gate++ <--> Channel <--> B.gate++;
        A.gate++ <--> Channel <--> C.gate++;
        A.gate++ <--> Channel <--> G.gate++;
        B.gate++ <--> Channel <--> C.gate++;
        B.gate++ <--> Channel <--> C.gate++;
        B.gate++ <--> Channel <--> E.gate++;
        C.gate++ <--> Channel <--> E.gate++;
        C.gate++ <--> Channel <--> F.gate++;
        G.gate++ <--> Channel <--> F.gate++;
        F.gate++ <--> Channel <--> H.gate++;
        E.gate++ <--> Channel <--> I.gate++;
        I.gate++ <--> Channel <--> X.gate++;
        F.gate++ <--> Channel <--> J.gate++;
        J.gate++ <--> Channel <--> K.gate++;
        K.gate++ <--> Channel <--> X.gate++;
        H.gate++ <--> Channel <--> L.gate++;
        F.gate++ <--> Channel <--> L.gate++;
}


