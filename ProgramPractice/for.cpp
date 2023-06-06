
typedef struct {
  int hour;
  int min;
} time;
typedef struct {
  int num;
  int position;
  time t;
  float money;
} Car;
typedef struct Node {
  Car data;
  struct Node *next;
} CQueueNode;
typedef struct {
  Car elem[NUM + 1];
  int top;
} Stack;
typedef struct {
  CQueueNode *front;
  CQueueNode *rear;
} LinkQueue;
void InitQueue(LinkQueue *Q);
// 初始化队列
int EnterQueue(LinkQueue *Q, Car *t); // 进队
void InitStack(Stack *S);
// 初始化栈
void Push(Stack *S, Car *r);
// 压栈
int IsEmpty(Stack *S);
// 判断栈空
int IsFull(Stack *S);
// 判断栈满
int GetTop(Stack *S, Car *n);
int DeleteQueue(LinkQueue *Q, Car *x);
void CarIn(Stack *S, LinkQueue *Q, Car *r);
void CostCalculate(Car *r, int h, int m);
void CarOut(Stack *S, Stack *S0, Car *r, LinkQueue *Q);