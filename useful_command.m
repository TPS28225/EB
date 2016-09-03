clear all
clc
CRC_method=[1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
%���������ļ��������ļ�����ı���ΪVoice��
load('voice_frag.mat')
%����A��ѹ�������������Ҫ��˫���ȸ�������ѹ����ȡ86.7�ͺã�64��ѹ�������ֵ��һ�루128��
Voice_a_compressed = (compand(double(Voice_frag),87.6,60,'a/compressor'))';
%����A�ɽ�ѹ�����������ΪA��ѹ��������������ֺ�֮ǰ��ֵһ�����������A�ɽ�ѹ���㷨
Voice_a_expander = (compand(Voice_a_compressed,87.6,60,'a/expander'))';
%Ϊ�˱�֤ת����bit������Ҫ��ѹ��ֵ��С�����ֽض�
Voice_a_compressed_int16=int16(Voice_a_compressed);
%��Ҫת����BIT�����Ѹ���ת�����������㷨��������������ȡ�෴�����ټ���127
temp=length(Voice_a_compressed_int16);
for i=1:temp
    if(Voice_a_compressed_int16(i,1)<0)
        Voice_a_compressed_int16(i,1)=-Voice_a_compressed_int16(i,1)+127;
    end  
end
%��ѹ���������ת���ɶ����ƣ�ÿ������ռ��һ�У���λ��ǰ
Voice_a_compressed_bin=de2bi(Voice_a_compressed_int16);
%������ת����BIT��
[Voice_a_compressed_bin_row, Voice_a_compressed_bin_clo]=size(Voice_a_compressed_bin);
%ע��reshape���������Ҫ��ת�ã���ת��������������Ȼ�ǵ�λ��ǰ
Voice_a_compressed_bitstream=reshape(Voice_a_compressed_bin',Voice_a_compressed_bin_clo*Voice_a_compressed_bin_row,1);
%crcУ��,����32λ��׼crcУ�����
CRC_Object=comm.CRCGenerator('Polynomial',CRC_method, 'ChecksumsPerFrame',4);
%ʹ�����ɵ�CRCУ����������������������
%ע�������������Ҫת����logicalģʽ
Voice_a_compressed_bitstream_CRC =step(CRC_Object,logical(Voice_a_compressed_bitstream));
%FSK/ASK/PSK/QPSK����

%������������
hAWGN = comm.AWGNChannel('NoiseMethod','Signal to noise ratio (SNR)','SNR',15);

% %PSK����
% %����PSK����8����Ʒ�ʽ��0ƫ�ƣ�bit����
% PSKhModulator = comm.PSKModulator(2,0,'BitInput',true);
% %����PSK�������
% PSKhDemod = comm.PSKDemodulator(2,0,'BitOutput',true);
% %�����ź�
% modSignal = step(PSKhModulator, Voice_a_compressed_bitstream_CRC);
% %��������
% % Pass the gauss channel with SNR=15dB��ԽС����Խ��
% noisySignal = awgn(modSignal,10,'measured'); 
% %���
% receivedData=step(PSKhDemod, noisySignal);
% % constellation(PSKhModulator);

% %FSK
% %����������
% FSKhMod = comm.FSKModulator(2,100);
% FSKhMod.BitInput=true;
% %���������
% FSKhDemod = comm.FSKDemodulator(2, 100);
% FSKhDemod.BitOutput=true;
% FSKhDemod.OutputDataType='logical';
% %�����ź�
% modSignal = step(FSKhMod, Voice_a_compressed_bitstream_CRC);
% %��������
% noisySignal = step(hAWGN, modSignal);
% %����ź�
% receivedData = step(FSKhDemod, noisySignal);


% %QPSK
% % ����QPSK���ƶ��� 
% QPSKhModulator = comm.QPSKModulator('BitInput',true);
% %����QPSK���
% QPSKhDemod = comm.QPSKDemodulator('BitOutput',true);
% % �ı���λ
% %  QPSKhModulator.PhaseOffset = pi/16;
% %���ݴ�����QPSK���ƶ������һ���ź�
% modSignal = step(QPSKhModulator, Voice_a_compressed_bitstream_CRC);
% %�����źż�������                     
% noisySignal = step(hAWGN, modSignal);
% %�������������źŽ��
% receivedData = step(QPSKhDemod, noisySignal); 
 
%PAM����
% Create a 2-PAM modulator System object with bits as inputs and Gray-coded signal constellation
PAMhModulator = comm.PAMModulator(2,'BitInput',true);
PAMhDemod = comm.PAMDemodulator(2);
% Modulate and plot the data
modSignal = step(PAMhModulator, Voice_a_compressed_bitstream_CRC); 
% %��������
noisySignal = step(hAWGN, modSignal);
% %����ź�
receivedData = step(PAMhDemod, noisySignal);
%constellation(PAMhModulator);


%���ƽ���������ͼ
scatterplot(modSignal);
scatterplot(noisySignal);
scatterplot(receivedData);











