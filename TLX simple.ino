/*
    Name:       TLX.ino
    Created:	15-02-2020 17:52:56
    Author:     TN-PC\Torben
    Board LOLIN D32
    Pin 16  :RXD2 Seriel in
    Pin 17  :RXD2 Seriel out
    R411A01 mini 3.3V Auto RS485 to TTL232 Converter Board used
*/ 

const unsigned short FCSTable[256] =
{
0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};


String RS485_SrcAddr = "0002"; //Program adresse
String RS485_StartFrame = "FF03";
String RS485_StartStop = "7E";
String RS485_DstAddr = "FFFF"; //Inverter Adressen "EAE4" 
String RS485_CRC    = "0000";
String PreGet       = "0A01C808D0"; //For ULX Change to "0A01C804D0"
String PostGet      = "8000000000"; 
String GetAddr      = "0015"; // B18B
String GetTotalP    = "0102";
String GetInstantP  = "0246";
String GetPvTemp    = "0204";
String GetOutTemp   = "0203";
String GetHZ        = "0250";
String GetTotalPDay = "024A";
String GetPvP1      = "0232";
String GetPvP2      = "0233";
String GetPvP3      = "0234";
String GetPvV1      = "0228";
String GetPvV2      = "0229";
String GetPvV3      = "022A";
String GetPvA1      = "022D";
String GetPvA2      = "022E";
String GetPvA3      = "02FA";
String GetGridV1    = "023C";
String GetGridV2    = "023D";
String GetGridV3    = "023E";
String GetProdTday  = "780A";
String GetProdTyear = "7832";
String GetProdL1year = "7833";
String GetProdL2year= "7834";
String GetProdL3year= "7835";
String GetProdL4year= "7836";
String GetProdL5year = "7837";
String GetProdL6year = "7838";
String GetProdL7year = "7839";
String GetProdL8year = "783A";

String GetOpMode    = "0A02";

#define BLYNK_PRINT Serial
#define RXD2 16
#define TXD2 17

String TXData ;
byte DataAsc[100];


void setup()
{
    Serial.begin(115200) ;	// Debug console
    Serial2.begin(19200, SERIAL_8N1, RXD2, TXD2);	// TLX
    delay(1000);
    Serial.println("Starter");
    FindInvAddr();
     Serial.println("Total Produktion            :" + String(GetInvData(GetTotalP) / 1000) + " KWh");
     Serial.println("Total Produktion Day        :" + String(GetInvData(GetTotalPDay) / 1000) + " KWh");
     Serial.println("Instant Energy Production   :" + String(GetInvData(GetInstantP) / 1000) + " KWh");
     Serial.println("Panel Temperature           :" + String(GetInvData(GetPvTemp) / 1) + " C");
     Serial.println("Out Temperature             :" + String(GetInvData(GetOutTemp) / 1) + " C");
     Serial.println("Total Produktion Day        :" + String(GetInvData(GetProdTday) / 1000) + " KWh");
     Serial.println("Net Frekvens                :" + String(GetInvData(GetHZ) / 1000) + " Hz");
     Serial.println("Grid Voltage L1             :" + String(GetInvData(GetGridV1) / 10) + " V");
     Serial.println("Grid Voltage L2             :" + String(GetInvData(GetGridV2) / 10) + " V");
     Serial.println("Grid Voltage L3             :" + String(GetInvData(GetGridV3) / 10) + " V");
     Serial.println("PV Power input P1           :" + String(GetInvData(GetPvP1) / 1) + " W");
     Serial.println("PV Power input P2           :" + String(GetInvData(GetPvP2) / 1) + " W");
     Serial.println("PV Power input P3           :" + String(GetInvData(GetPvP3) / 1) + " W");
     Serial.println("PV Voltage input P1         :" + String(GetInvData(GetPvV1) / 10) + " V");
     Serial.println("PV Voltage input P2         :" + String(GetInvData(GetPvV2) / 10) + " V");
     Serial.println("PV Voltage input P3         :" + String(GetInvData(GetPvV3) / 10) + " V");
     Serial.println("PV Current input P1         :" + String(GetInvData(GetPvA1) / 1000) + " A");
     Serial.println("PV Current input P2         :" + String(GetInvData(GetPvA2) / 1000) + " A");
     Serial.println("PV Current input P3         :" + String(GetInvData(GetPvA3) / 1000) + " A");
     Serial.println("Production this year        :" + String(GetInvData(GetProdTyear) / 1000) + " KWh");
     Serial.println("Production 1 years ago      :" + String(GetInvData(GetProdL1year) / 1000) + " KWh");
     Serial.println("Production 2 years ago      :" + String(GetInvData(GetProdL2year) / 1000) + " KWh");
     Serial.println("Production 3 years ago      :" + String(GetInvData(GetProdL3year) / 1000) + " KWh");
     Serial.println("Production 4 years ago      :" + String(GetInvData(GetProdL4year) / 1000) + " KWh");
     Serial.println("Production 5 years ago      :" + String(GetInvData(GetProdL5year) / 1000) + " KWh");
     Serial.println("Production 6 years ago      :" + String(GetInvData(GetProdL6year) / 1000) + " KWh");
     Serial.println("Production 7 years ago      :" + String(GetInvData(GetProdL7year) / 1000) + " KWh");
     Serial.println("Production 8 years ago      :" + String(GetInvData(GetProdL8year) / 1000) + " KWh");
     Serial.println("Operation mode              :" + String(GetInvData(GetOpMode)) + " M");

 //   Serial.println(RXData);
}

void loop()
{
    delay(1000);
    }

float GetInvData(String GetLocal){
    String RXData;
    TX_TLX(GetLocal);
    RXData = RX_TLX();
    return HexToDec(RXData.substring(36, 36 + 2) + RXData.substring(34, 34 + 2) + RXData.substring(32, 32 + 2) + RXData.substring(30, 30 + 2));
}

String RX_TLX() {
    String RxBuffer;
    String RXData = "";
    delay(25);
    while (Serial2.available() > 0) {
        RxBuffer = String(Serial2.read(), HEX);
        if (RxBuffer.length() == 1)  RxBuffer = "0" + RxBuffer;
        RXData = RXData + RxBuffer;
    }
    RXData.toUpperCase();
    RXData.replace("7D5E", "7E");
    RXData.replace("7D5D", "7D");
    return RXData;
}

void FindInvAddr() {
    TX_TLX(GetAddr);
    RS485_DstAddr = RX_TLX().substring(6, 6 + 4);
}

void TX_TLX(String TXLocal) {
    int x;
    TXData = RS485_StartFrame + RS485_SrcAddr + RS485_DstAddr + PreGet + TXLocal + PostGet;
    TXData = RS485_StartStop + TXData + pppfcs16(DataAsc, ChrHex2Asc()) + RS485_StartStop;
//    Serial.println(TXData + " Send ");
    for (x = 0; x < TXData.length(); x = x + 2) {
     Serial2.write(HexToDec(TXData.substring(x, x + 2)));
    }
}

unsigned int ChrHex2Asc() {
    int y = 0;
    for (int x = 0; x < TXData.length(); x = x + 2) {
        DataAsc[y] = HexToDec(TXData.substring(x, x + 2));
        y++;
    }
    return y;
}

String pppfcs16(byte* pByte, int length)
{
    int fcs = 0xFFFF;
    while (length--)
        fcs = (fcs >> 8) ^ FCSTable[(fcs ^ *pByte++) & 0xff];
    fcs ^= 0xFFFF;
    String str_fcs = String(fcs, HEX);
    str_fcs = str_fcs.substring(2, 4) + str_fcs.substring(0, 2);
    return str_fcs;
}

int HexToDec(String hexString) {
    int decValue = 0;
    int nextInt;
    for (int i = 0; i < hexString.length(); i++) {
        nextInt = int(hexString.charAt(i));
        if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
        if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
        if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
        nextInt = constrain(nextInt, 0, 15);
        decValue = (decValue * 16) + nextInt;
    }

        if (decValue > 0x7FFFFFFF) {
        decValue -= 0x100000000;
    }
    return decValue;
}
