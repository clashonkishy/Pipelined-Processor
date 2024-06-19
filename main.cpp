#include <bits/stdc++.h>
using namespace std;

ifstream ifile;
ifstream dfile;
ifstream rfile;
ofstream ofile;
ofstream odfile;

vector<string> instructions(0);           //vector to store instructions from ICache.txt
vector<int> registers(0);                 //vector to store register data from RF.txt
vector<int> dataC(0);                     //vector to store data from DCache.txt
char reg1, reg2, reg3, imm;
int pc = 0, clk = 0, dh = 0, ch = 0;
set<int> reg;                             // to keep track of register where data is written to so we can know if it is being used in the next instruction
int htd(char c) //hexadecimal character to decimal
{
    int h = ((isdigit(c)) ? (c - '0') : (c - 'a' + 10));
    return h;
}
char dth(int c)   // decimal to hexadecimal character
{
    char f = 'a', g = '0';
    char h = (c > 9 ? 'a' + c - 10 : '0' + c);
    return h;
}
void ADD()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 4;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end()) | (reg.find(htd(reg3)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] + registers[htd(reg3)];
}

void SUB()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end()) | (reg.find(htd(reg3)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] - registers[htd(reg3)];
}

void MUL()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end()) | (reg.find(htd(reg3)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] * registers[htd(reg3)];
}

void INC()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)]++;
}

void AND()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end()) | (reg.find(htd(reg3)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] & registers[htd(reg3)];
}

void OR()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end()) | (reg.find(htd(reg3)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] | registers[htd(reg3)];
}

void XOR()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end()) | (reg.find(htd(reg3)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] ^ registers[htd(reg3)];
}

void NOT()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    reg3 = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = ~registers[htd(reg2)];
}

void SLLI()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] << htd(imm);
}

void SRLI()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = registers[htd(reg2)] >> htd(imm);
}

void LI()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = htd(reg2) * 16 + htd(imm);
}

void LD()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] = dataC[2 * registers[htd(reg2)] + 2 * htd(imm)] * 16 + dataC[2 * registers[htd(reg2)] + 2 * htd(imm) + 1];
}

void ST()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end()) | (reg.find(htd(reg2)) != reg.end());
    // to check if the registers are being written into in previous instruction
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    registers[htd(reg1)] %= 256;
    dataC[2 * registers[htd(reg2)] + 2 * htd(imm)] = (registers[htd(reg1)] / 16);
    dataC[2 * registers[htd(reg2)] + 2 * htd(imm) + 1] = registers[htd(reg1)] - (registers[htd(reg1)] / 16) * 16;
    // cout<<dataC[2 * registers[htd(reg2)]  + 2 * htd(imm)]<<dataC[2 * registers[htd(reg2)]  + 2 * htd(imm)+1]<<" "<<2 * registers[htd(reg2)]  + 2 * htd(imm)<<endl;
}

void JMP()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    int temp = (htd(reg1) << 4) + htd(reg2);
    if (clk == 0)
        clk += 5;
    else
        clk++;
    ch++;
    clk += 2;
    reg.clear();
    // talking 2's complement if negative
    if (temp >= (1 << 7))
    {
        temp = (1 << 8) - temp - 1;
        pc = pc - temp - 1;
        return;
    }
    pc = pc + temp - 1;
}

void BEQZ()
{
    reg1 = instructions[pc][1];
    reg2 = instructions[pc][2];
    imm = instructions[pc][3];
    int temp = (htd(reg2) << 4) + htd(imm);
    // cout << htd(reg1) <<" "<<htd(reg2)<<" "<<htd(imm)<<" "<<temp<<endl;
    if (clk == 0)
        clk += 5;
    else
        clk++;
    bool g = (reg.find(htd(reg1)) != reg.end());
    if (g)
    {
        clk++;
        dh++;
    }
    reg.clear();
    reg.insert(htd(reg1));
    clk += 2;
    ch++;
    // talking 2's complement if negative
    if (temp >= (1 << 7))
    {
        temp = (1 << 8) - temp - 1;
        if (registers[htd(reg1)] == 0)
        {
            pc = pc - temp - 1;
            return;
        }
    }
    if (registers[htd(reg1)] == 0)
    {
        pc = pc + temp;
    }
}

int main(int argc, char *argv[])
{

    ifile.open(argv[1], ios::in);
    string gar, gar2;
    while (ifile >> gar)
    {
        ifile >> gar2;
        gar += gar2;
        // cout << gar << endl;
        instructions.push_back(gar);
    }
    dfile.open(argv[2], ios::in);
    char data;
    while (dfile >> data)
    {
        int d = htd(data);
        dataC.push_back(d);
    }
    rfile.open(argv[3], ios::in);
    char v1, v2;
    while (rfile >> v1 >> v2)
    {
        int d1 = htd(v1);
        int d2 = htd(v2);
        // cout<<d1<<d2<<endl;
        registers.push_back(d1 * 16 + d2);
    }
    ofile.open(argv[4], ios::out);
    odfile.open(argv[5], ios::out);
    char opcode;
    // creating a function pointer array;
    void (*operations[])() = {ADD, SUB, MUL, INC, AND, OR, XOR, NOT, SLLI, SRLI, LI, LD, ST, JMP, BEQZ};
    int a = 0;
    int ai = 0, li = 0, si = 0, mi = 0, ci = 0, hi = 0, lii = 0;
    // variables to count arithmetic, logical, shift, memory, control, halt, load immediate instructions
    while (true)
    {
        opcode = instructions[pc][0];
        int op = (isdigit(opcode)) ? (opcode - '0') : (tolower(opcode) - 'a' + 10);
        // cout << op << endl;
        if (op == 15)
        {
            hi++;
            clk++;
            break;
        }
        if (op >= 0 && op < 4)
            ai++;
        else if (op >= 4 && op < 8)
            li++;
        else if (op >= 8 && op < 10)
            si++;
        else if (op == 10)
            lii++;
        else if (op >= 11 && op < 13)
            mi++;
        else if (op >= 13 && op < 15)
            ci++;
        // if(a==100)break;
        // for(auto i:registers){
        //     cout<<i<<"  ";
        // }
        // cout<<endl;
        operations[op]();
        a++;
        pc++;
    }
    int k = 0;
    for (auto i : dataC)
    {
        char c = dth(i);
        odfile << c;
        k++;
        if (k % 2 == 0)
            odfile << endl;
    }
    clk = clk + dh;
    cout << clk;
    dh *= 2;
    ch *= 2;
    ofile << "Total number of instructions executed        : " << ai + li + si + lii + mi + ci + hi << endl;
    ofile << "Number of instructions in each class     " << endl;
    ofile << "Arithmetic instructions                      : " << ai << endl;
    ofile << "Logical instructions                         : " << li << endl;
    ofile << "Shift instructions                           : " << si << endl;
    ofile << "Memory instructions                          : " << mi << endl;
    ofile << "Load immediate instructions                  : " << lii << endl;
    ofile << "Control instructions                         : " << ci << endl;
    ofile << "Halt instructions                            : " << hi << endl;
    ofile << "Cycles Per Instruction                       : " << (double)clk / (double)(ai + li + si + lii + mi + ci + hi) << endl;
    ofile << "Total number of stalls                       : " << dh + ch << endl;
    ofile << "Data stalls (RAW)                            : " << dh << endl;
    ofile << "Control stalls                               : " << ch << endl;
}