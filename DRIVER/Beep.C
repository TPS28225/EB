#include "main.h"
// ���������������ֵ��λ��Hz��
#define L1 262
#define L2 294
#define L3 330
#define L4 349
#define L5 392
#define L6 440
#define L7 494

// ������������
#define M1 523
#define M2 587
#define M3 659
#define M4 698
#define M5 784
#define M6 880
#define M7 988

// �����������
#define H1 1047
#define H2 1175
#define H3 1319
#define H4 1397
#define H5 1568
#define H6 1760
#define H7 1976

// ����ʱֵ��λ�����������ٶȣ���ֵ��λ��ms��
#define TT 2000

typedef struct
{
  short mName; // ������ȡֵL1��L7��M1��M7��H1��H7�ֱ��ʾ������������������1234567��ȡֵ0��ʾ��ֹ��
  short mTime; // ʱֵ��ȡֵT��T/2��T/4��T/8��T/16��T/32�ֱ��ʾȫ�����������������ķ��������˷�����.��ȡֵ0��ʾ�������
}tNote;


// �������������»�����ϲ���ơ�
const tNote MyScore[]=
{
  {L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M3,TT/8},{M3,TT/4},{L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M6,TT/8},{M6,TT/2},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},
  {M1,TT/8},{L6,TT/4},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},{M1,TT/8},{M2,TT/4},{M2,TT/8+TT/16},{M1,TT/8},{M1,TT/4},{M2,TT/4},{M3,TT/4},{M5,TT/4},{M6,TT},{M6,TT/8+TT/16},{M5,TT/16},
  {M3,TT/8},{M5,TT/8},{M6,TT/4}, //��ϲ�㷢�ơ���������˲���
  
  {L3,TT/8},{L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/8},{L3,TT/8},{L3,TT/8},{L5,TT/8},{L6,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/8},{L6,TT/4},{L3,TT/8},{L5,TT/8},{M1,TT/4},{M1,TT/8},{M1,TT/8},{M2,TT/8},
  {M2,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L3,TT/8},{M2,TT/4},{M2,TT/8},{M1,TT/8},{M2,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/8},
  {M1,TT/8},{M3,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M3,TT/4},{L5,TT/4},{L6,TT/2},//��ף�����µ�Ů�����������̳������Դ�

  {L3,TT/8},{L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/8},{L3,TT/8},{L3,TT/8},{L5,TT/8},{L6,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/8},{L6,TT/4},{L3,TT/8},{L5,TT/8},{M1,TT/4},{M1,TT/8},{M1,TT/8},{M2,TT/8},
  {M2,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L3,TT/8},{M2,TT/4},{M2,TT/8},{M1,TT/8},{M2,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/8},
  {M1,TT/8},{M3,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M3,TT/4},{L5,TT/4},{L6,TT/2},//��ף�����µ�Ů�����������̳������Դ�

  {L5,TT/4},{M1,TT/2+TT/4},{M1,TT/8},{M2,TT/8},{M3,TT/2+TT/4},{M3,TT/8},{M5,TT/8},{M5,TT/4+TT/8},{M3,TT/8},{M2,TT/4},{M1,TT/4},{M2,TT/2},{M2,TT/4+TT/8},{L6,TT/8},{M2,TT/4},{M3,TT/4},
  {M4,TT/8+TT/16},{M5,TT/16},{M4,TT/8},{M3,TT/8},{M2,TT/2},{M5,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/4},{L5,TT/8},{L6,TT/2},//��ҡ��ڡ�����Ҫ���ù�����

  {L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M3,TT/8},{M3,TT/4},{L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M6,TT/8},{M6,TT/2},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},
  {M1,TT/8},{L6,TT/4},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},{M1,TT/8},{M2,TT/4},{M2,TT/8+TT/16},{M1,TT/8},{M1,TT/4},{M2,TT/4},{M3,TT/4},{M5,TT/4},{M6,TT},{M6,TT/8+TT/16},{M5,TT/16},
  {M3,TT/8},{M5,TT/8},{M6,TT/4}, //��ϲ�㷢�ơ���������˲���

  {L3,TT/8},{L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/8},{L3,TT/8},{L3,TT/8},{L5,TT/8},{L6,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/8},{L6,TT/4},{L3,TT/8},{L5,TT/8},{M1,TT/4},{M1,TT/8},{M1,TT/8},{M2,TT/8},
  {M2,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L3,TT/8},{M2,TT/4},{M2,TT/8},{M1,TT/8},{M2,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/8},
  {M1,TT/8},{M3,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M3,TT/4},{L5,TT/4},{L6,TT/2},//��ף�����µ�Ů�����������̳������Դ�

  {L5,TT/4},{M1,TT/2+TT/4},{M1,TT/8},{M2,TT/8},{M3,TT/2+TT/4},{M3,TT/8},{M5,TT/8},{M5,TT/4+TT/8},{M3,TT/8},{M2,TT/4},{M1,TT/4},{M2,TT/2},{M2,TT/4+TT/8},{L6,TT/8},{M2,TT/4},{M3,TT/4},
  {M4,TT/8+TT/16},{M5,TT/16},{M4,TT/8},{M3,TT/8},{M2,TT/2},{M5,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/4},{L5,TT/8},{L6,TT/2},//��ҡ��ڡ�����Ҫ���ù�����

  {L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M3,TT/8},{M3,TT/4},{L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M6,TT/8},{M6,TT/2},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},
  {M1,TT/8},{L6,TT/4},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},{M1,TT/8},{M2,TT/4},{M2,TT/8+TT/16},{M1,TT/8},{M1,TT/4},{M2,TT/4},{M3,TT/4},{M5,TT/4},{M6,TT},{M6,TT/8+TT/16},{M5,TT/16},
  {M3,TT/8},{M5,TT/8},{M6,TT/4}, //��ϲ�㷢�ơ���������˲���

  {L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M3,TT/8},{M3,TT/4},{L3,TT/8},{M6,TT/4},{M5,TT/4},{M6,TT/4},{M5,TT/8},{M6,TT/8},{M6,TT/2},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},
  {M1,TT/8},{L6,TT/4},{M3,TT/8},{M2,TT/8+TT/16},{M3,TT/16},{M2,TT/8},{M1,TT/8},{M2,TT/4},{M2,TT/8+TT/16},{M1,TT/8},{M1,TT/4},{M2,TT/4},{M3,TT/4},{M5,TT/4},{M6,TT},{M6,TT/8+TT/16},{M5,TT/16},
  {M3,TT/8},{M5,TT/8},{M6,TT/4}, //��ϲ�㷢�ơ���������˲���
  {0,0},
};




// ������������������ɫ��
//const tNote MyScore[]=
//{
//  {M1,TT/8},{M1,TT/4},{L6,TT/8},{L5,TT/4},{L6,TT/4},{M1,TT/4},{M1,TT/8},{M2,TT/8},{M3,TT/2},{M2,TT/8},{M2,TT/4},{M1,TT/8},{M2,TT/4},{M2,TT/8},{M5,TT/8},{M5,TT/8},{M3,TT/8},
//  {M3,TT/8},{M2,TT/8},{M3,TT/2},{M1,TT/8},{M1,TT/4},{L6,TT/8},{L5,TT/4},{M5,TT/4},{M3,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{M2,TT/8},{M2,TT/4},//��ã���������ҵİ���������ѽ��ҡ
//  {M1,TT/8},{M2,TT/8},{M2,TT/4},{M3,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/8},{M2,TT/8},{M1,TT/2},//��һ��ʱ�⡣��������������������������
//  {M1,TT/8},{M1,TT/4},{L6,TT/8},{L5,TT/4},{L6,TT/4},{M1,TT/8},{M1,TT/4},{M2,TT/8},{M3,TT/2},{M2,TT/8},{M2,TT/4},{M1,TT/8},{M2,TT/4},{M2,TT/8},{M5,TT/8},{M5,TT/8},{M3,TT/8},
//  {M3,TT/8},{M2,TT/8},{M3,TT/2},{M1,TT/8},{M1,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/4},{M5,TT/4},{M3,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{M2,TT/8},{M2,TT/4},//��ã���������ҵİ���������ѽ��ҡ
//  {M1,TT/8},{M2,TT/8},{M2,TT/4},{M3,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/8},{M2,TT/8},{M1,TT/2},//ө��档����˭������һ����ҹ������
//  {M3,TT/8},{M5,TT/4},{M5,TT/8},{M5,TT/4},{M5,TT/4},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{M6,TT/8},{H1,TT/8},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},
//  {L6,TT/8},{M2,TT/4},{M2,TT/8},{M3,TT/8},{M3,TT/8},{M2,TT/4+TT/8},{M3,TT/8},{M5,TT/4},{M5,TT/8},{M5,TT/4},{M5,TT/4},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},//��ã���������ҵİ���������ѽ��ҡ
//  {M1,TT/2},{L6,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/8},{M2,TT/4},{M3,TT/4},{M1,TT/2+TT/4},	//����ֻ�����������������ˮ����
//  {M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT},{M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},{M1,TT/8},{M2,TT/8},{M2,TT},{M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},
//  {M2,TT/8},{M1,TT/8},{L6,TT/2},{L6,TT/8},{L5,TT/8},{M1,TT/8},{M2,TT/8},{M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},{M1,TT/8},{L6,TT/8},{M1,TT},
//  {M1,TT/8},{M1,TT/4},{L6,TT/8},{L5,TT/4},{L6,TT/4},{M1,TT/8},{M1,TT/4},{M2,TT/8},{M3,TT/2},{M2,TT/8},{M2,TT/4},{M1,TT/8},{M2,TT/4},{M2,TT/8},{M5,TT/8},{M5,TT/8},{M3,TT/8},
//  {M3,TT/8},{M2,TT/8},{M3,TT/2},{M1,TT/8},{M1,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/4},{M5,TT/4},{M3,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{M2,TT/8},{M2,TT/4},//��ã���������ҵİ���������ѽ��ҡ
//  {M1,TT/8},{M2,TT/8},{M2,TT/4},{M3,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/8},{M2,TT/8},{M1,TT/2},//ө��档����˭������һ����ҹ������
//  {M3,TT/8},{M5,TT/4},{M5,TT/8},{M5,TT/4},{M5,TT/4},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{M6,TT/8},{H1,TT/8},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},
//  {L6,TT/8},{M2,TT/4},{M2,TT/8},{M3,TT/8},{M3,TT/8},{M2,TT/4+TT/8},{M3,TT/8},{M5,TT/4},{M5,TT/8},{M5,TT/4},{M5,TT/4},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},//��ã���������ҵİ���������ѽ��ҡ
//  {M1,TT/2},{L6,TT/8},{M1,TT/8},{L6,TT/8},{L5,TT/8},{M2,TT/4},{M3,TT/4},{M1,TT/2+TT/4},	//����ֻ�����������������ˮ����
//  {M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT},{M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},{M1,TT/8},{M2,TT/8},{M2,TT},{M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},
//  {M2,TT/8},{M1,TT/8},{L6,TT/2},{L6,TT/8},{L5,TT/8},{M1,TT/8},{M2,TT/8},{M1,TT/4+TT/8},{M5,TT/8},{M1,TT/8},{M5,TT/8},{M1,TT/8},{L6,TT/8},{M1,TT},

//  {0,0},
//};



// ��������������������硷
//const tNote MyScore[]=
//{
//  {L6,TT/4},{L3,TT/8},{L5,TT/8},{L6,TT/4},{L6,TT/8},{M1,TT/8},{M1,TT/4},{M2,TT/8},{M1,TT/8},{L6,TT/2},{M1,TT/4},{M1,TT/8},{L5,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M5,TT/8},
//  {M5,TT/8},{M3,TT/8},{M2,TT/4},{M3,TT/2},{M6,TT/8},{M6,TT/8},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M3,TT/4},{M1,TT/8},{L6,TT/8},{L6,TT/8},{L6,TT/8},{M3,TT/8},//��ã���������ҵİ���������ѽ��ҡ
//  {M2,TT/2},{M3,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/4},{L5,TT/4},{L6,TT/2}, //�ڣ�ʲô���ĸ����������
//  {L6,TT/4},{L3,TT/8},{L5,TT/8},{L6,TT/4},{L6,TT/8},{M1,TT/8},{M1,TT/4},{M2,TT/8},{M1,TT/8},{L6,TT/2},{M1,TT/4},{M1,TT/8},{L5,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M5,TT/8},
//  {M5,TT/8},{M3,TT/8},{M2,TT/4},{M3,TT/2},{M6,TT/8},{M6,TT/8},{M6,TT/8},{M5,TT/8},{M3,TT/8},{M3,TT/4},{M1,TT/8},{L6,TT/8},{L6,TT/8},{L6,TT/8},{M3,TT/8},//��ã���������ҵİ���������ѽ��ҡ
//  {M2,TT/2},{M3,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{L6,TT/4},{L5,TT/4},{L6,TT/2}, //�ڣ�ʲô���ĸ����������
//  {M3,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M3,TT/8},{M5,TT/8},{M5,TT/8},{M6,TT/8},{H1,TT/8},{M6,TT/8},{M5,TT/4},{M6,TT/2},{L6,TT/4},{L6,TT/8},
//  {L5,TT/8},{L6,TT/4},{M1,TT/4},{M2,TT/8},{M3,TT/16},{M2,TT/16},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L6,TT/8},{M6,TT/8},{M6,TT/8},{M5,TT/8},{M2,TT/8},{M3,TT/16},{M2,TT/16},
//  {M1,TT/8},{M2,TT/8},{M3,TT/2},//������
//  {M1,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/4},{L5,TT/8},{L5,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{L6,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},
//  {L5,TT/8},{L3,TT/8},{L6,TT/2},{L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/4},{M1,TT/4},{M2,TT/8},{M3,TT/16},{M2,TT/16},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L6,TT/8},{M6,TT/8},
//  {M6,TT/8},{M5,TT/8},{M2,TT/8},{M3,TT/16},{M2,TT/16},
//  {M1,TT/8},{M2,TT/8},{M3,TT/2},//������
//  {M1,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/4},{L5,TT/8},{L5,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/4+TT/8},{M1,TT/8},{L6,TT/8},
//  {M1,TT/8},{M2,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M3,TT/8},{M5,TT/8},{M6,TT/2},{M6,TT/2},{L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/4},
//  {L6,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/16},{M2,TT/16},{M1,TT/8},{M2,TT/8},{M3,TT/2},
//  {M6,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},{M1,TT/2},//����������������̨
//  {L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/4},{M1,TT/4},{M2,TT/8},{M3,TT/16},{M2,TT/16},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L6,TT/8},{M6,TT/8},{M6,TT/8},{M5,TT/8},{M2,TT/8},{M3,TT/16},{M2,TT/16},
//  {M1,TT/8},{M2,TT/8},{M3,TT/2},//������
//  {M1,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/4},{L5,TT/8},{L5,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/2},{L6,TT/8},{M1,TT/8},{M2,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/8},
//  {L5,TT/8},{L3,TT/8},{L6,TT/2},{L6,TT/4},{L6,TT/8},{L5,TT/8},{L6,TT/4},{M1,TT/4},{M2,TT/8},{M3,TT/16},{M2,TT/16},{M1,TT/8},{M2,TT/8},{M3,TT/2},{L6,TT/8},{M6,TT/8},
//  {M6,TT/8},{M5,TT/8},{M2,TT/8},{M3,TT/16},{M2,TT/16},
//  {M1,TT/8},{M2,TT/8},{M3,TT/2},//������
//  {M1,TT/8},{L6,TT/8},{L6,TT/8},{M1,TT/8},{M2,TT/4},{L5,TT/8},{L5,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M2,TT/8},{M1,TT/4+TT/8},{M1,TT/8},{L6,TT/8},
//  {M1,TT/8},{M2,TT/8},{M3,TT/8},{M5,TT/8},{M3,TT/8},{M3,TT/8},{M5,TT/8},{M6,TT/2},{M6,TT/2},
//  {0,0},
//};
u8 count = 0;

void BEEP_Run(void)
{		
	if(OUTPUTDEVICE.Beep == 0)
	{
		BEEP_OFF;
	}
	else
	{
		count = ! count;
		if(count==0)
			BEEP_ON;
		else
			BEEP_OFF;
	}
}

void BEEP_Configuration(void)
{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(BEEP_RCC, ENABLE); 						 
//			
//	GPIO_InitStructure.GPIO_Pin =  BEEP_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_Init(BEEP_GPIO, &GPIO_InitStructure);	
}



//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

void TIM9_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM9ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTEʱ��	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);

	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;           //GPIOE5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(BEEP_GPIO,&GPIO_InitStructure);              //��ʼ��PE5

	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��9
	
	
	//��ʼ��TIM9 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1	

	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  //ʹ��TIM9��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_CtrlPWMOutputs(TIM9,ENABLE);
	TIM_SetCompare1(TIM9,0);	
	
	TIM_Cmd(TIM9, ENABLE);  //ʹ��TIM9
}


// ������ֹͣ����
void buzzerQuiet(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_Cmd(TIM9, DISABLE);  //ֹͣTIM9
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;				 //PE.5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;        //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(BEEP_GPIO, &GPIO_InitStructure);	 //�����趨������ʼ��GPIOE.5
	GPIO_ResetBits(BEEP_GPIO,BEEP_PIN);	//PE.5 �����
}

/////////////////////////////////////////////////////////	 
//����������ָ��Ƶ�ʵ�����
//usFreq�Ƿ���Ƶ�ʣ�ȡֵ (ϵͳʱ��/65536)+1 �� 20000����λ��Hz
void buzzerSound(unsigned short usFreq)	 
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  unsigned long  ulVal;
  if((usFreq<=8000000/65536UL)||(usFreq>20000))
  {
    buzzerQuiet();// ����������
  }
  else
  {
		GPIO_InitStructure.GPIO_Pin = BEEP_PIN;           //GPIOE5
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
		GPIO_Init(BEEP_GPIO,&GPIO_InitStructure);              //��ʼ��PE5  
		ulVal=8000000/usFreq;
		TIM9->ARR =ulVal ;	//�����Զ���װ�ؼĴ������ڵ�ֵ�������� 
		TIM_SetCompare1(TIM9,ulVal /2);//����
    TIM_Cmd(TIM9, ENABLE);  //����TIM9
  }  
}

// ��������
void musicPlay(void) 
{ 
	u8 i=0; 
	while(1) 
	{ 
		if (MyScore[i].mTime == 0) break; 
		buzzerSound(MyScore[i].mName); 
		OSTimeDlyHMSM(0,0,0,MyScore[i].mTime);//
		i++; 
		buzzerQuiet(); // ����������
		OSTimeDlyHMSM(0,0,0,10);// 10 ms 
	} 
} 

//void musicPlay(void) 
//{ 
//	u8 i=0; 
//	while(1) 
//	{ 
//		if (MyScore[i].mTime == 0) break; 
//		buzzerSound(MyScore[i].mName); 
//			 delay_ms(MyScore[i].mTime);
//		i++; 
//		buzzerQuiet(); // ����������
//		delay_ms(10);// 10 ms 
//	} 
//} 

//int main(void) 
//{ 
//	delay_init();	    	 //��ʱ������ʼ��	  
//	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	TIM9_PWM_Init(14399,10);	 //��Ƶ��PWMƵ��=72000/14400/11��Khz��
//	for (;;) 
//	{ 
//		musicPlay(); 
////		delay_ms(1500); 
////		delay_ms(1500); 
//	} 
//}

void Beep_Config(void)
{
	TIM9_PWM_Init(14399,10);	 //��Ƶ��PWMƵ��=72000/14400/11��Khz��
}



















