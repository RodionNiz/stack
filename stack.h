#ifndef STACKH

#define STACKH

#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#ifdef DEBUG 

#define ON_DBG(...) __VA_ARGS__

#define ASSERT_STK_OK(stk, callLine) \
    if (StackOk (stk, __LINE__, callLine) != 0)\
    {\
        abort ();\
    }\

#define StackCtorCall(stk, capacity) \
    StackCtor (&stk, capacity ON_DBG(, __FILE__, #stk, __FUNCTION__, __LINE__));

#define StackPushCall(stk, pushingElem) \
    StackPush (&stk, pushingElem ON_DBG(, __LINE__));

#define StackPopCall(stk, popped) \
    StackPop (&stk, &popped ON_DBG(, __LINE__));

#define PrintStackCall(stk) \
    PrintStack (&stk ON_DBG(, __LINE__));

#else

#define ON_DBG(...)

#define ASSERT_STK_OK(stk, callLine)

#define StackCtorCall(stk, capacity)\
    StackCtor (&stk, capacity);

#define StackPushCall(stk, pushingElem) \
    StackPush (&stk, pushingElem)

#define StackPopCall(stk) \
    StackPop (&stk);

#define PrintStackCall(stk) \
    PrintStack (&stk);
    
#endif

#define ON_CANARY
#define ON_HASH

struct stack_t
{
    #ifdef ON_CANARY
    stackElem_t leftCanary;
    #endif

    stackElem_t* data;
    size_t capacity;
    size_t size;

    ON_DBG(const char* file;
           const char* name;
           const char* func;
           size_t line;)

    #ifdef ON_HASH
    size_t dataHash;
    size_t struckHash;
    #endif

    #ifdef ON_CANARY
    stackElem_t rightCanary;
    #endif
};

enum ErrorCodes
{
    StackIsOk = 0,
    StackPtrIsNullptr = (1 << 0),           //1
    DataInStackPtrIsNullptr = (1 << 1),     //2
    InvalidCapacityValue = (1 << 2),        //4
    InvalidSizeValue = (1 << 3),            //8
    SizeBiggerCapacity = (1 << 4),          //16
    InvalidElemValue = (1 << 5),            //32
    InvalidPoisonValue = (1 << 6),          //64
    DestroyingErr = (1 << 7),               //128
    ReallocationErr = (1 << 8),             //256
    StackUnderFlow = 3

    #ifdef ON_CANARY
    ,
    LeftStkCanErr = (1 << 9),               //512
    RightStkCanErr = (1 << 10),             //1024
    LeftDataCanErr = (1 << 11),             //2048
    RightDataCanErr = (1 << 12)             //4096
    #endif

    #ifdef ON_HASH
    ,
    InvalidDataHash = (1 << 13),            //8192
    InvalidStructHash = (1 << 14)           //16384
    #endif
};

#define ACURACY 0.0001

const stackElem_t GLOBAL_STACK_POISON = NAN;

const stackElem_t GLOBAL_LEFT_DATA_FOPF = 0xB1BAEB1B0BA;
const stackElem_t GLOBAL_RIGHT_DATA_FOPF = 0xB0BAEB1B1BA;

const stackElem_t GLOBAL_LEFT_STACK_FOPF = 0x51AC04C0;
const stackElem_t GLOBAL_RIGHT_STACK_FOPF = 0xBEDA2A3EA9EB1DEDA;


ErrorCodes StackCtor (stack_t* stk, size_t capacity ON_DBG(, const char* file, const char* name, const char* func, size_t line));
int StackDestroy (stack_t* stk ON_DBG(, size_t callLine));

ErrorCodes StackPush (stack_t* stk, stackElem_t pushingElem ON_DBG(, size_t callLine));
ErrorCodes StackPop  (stack_t* stk, stackElem_t* poppedElem ON_DBG(, size_t callLine));

ErrorCodes PrintStack (stack_t* const stk ON_DBG(, size_t callLine));

ErrorCodes StkCpcUp   (stack_t* stk ON_DBG(, size_t callLine));
ErrorCodes StkCpcDown (stack_t* stk ON_DBG(, size_t callLine));

size_t StackOk (stack_t* stk, size_t assertLine, size_t checkingFuncCallLine);

void StackDump (stack_t* stk, size_t reason, size_t errLine, size_t checkingFuncCallLine);

#ifdef ON_CANARY
int CheckCanary (stackElem_t canary, stackElem_t trueValue);
#endif 

int CmpDouble (double first, double second);

#ifdef ON_HASH
size_t DJB2_HashCount (stack_t* stk);
size_t DJB2_HashStruct (stack_t* stk);
#endif

#endif