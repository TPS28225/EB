clear all
clc
CRC_method=[1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
%加载声音文件（声音文件输出的变量为Voice）
load('voice_frag.mat')
%采用A律压缩，输入矩阵需要是双精度浮点数，压缩率取86.7就好，64是压缩后最大值的一半（128）
Voice_a_compressed = (compand(double(Voice_frag),87.6,60,'a/compressor'))';
%采用A律解压缩，输入矩阵为A律压缩矩阵，其他两项保持和之前的值一样，最后填入A律解压缩算法
Voice_a_expander = (compand(Voice_a_compressed,87.6,60,'a/expander'))';
%为了保证转化成bit流，需要将压缩值的小数部分截断
Voice_a_compressed_int16=int16(Voice_a_compressed);
%需要转化成BIT流，把负数转换成正数，算法是遇到负数，先取相反数，再加上127
temp=length(Voice_a_compressed_int16);
for i=1:temp
    if(Voice_a_compressed_int16(i,1)<0)
        Voice_a_compressed_int16(i,1)=-Voice_a_compressed_int16(i,1)+127;
    end  
end
%将压缩后的数据转化成二进制，每个数字占用一行，低位在前
Voice_a_compressed_bin=de2bi(Voice_a_compressed_int16);
%二进制转化成BIT流
[Voice_a_compressed_bin_row, Voice_a_compressed_bin_clo]=size(Voice_a_compressed_bin);
%注意reshape的输入矩阵要先转置，再转换成列向量，仍然是低位在前
Voice_a_compressed_bitstream=reshape(Voice_a_compressed_bin',Voice_a_compressed_bin_clo*Voice_a_compressed_bin_row,1);
%crc校验,生成32位标准crc校验对象
CRC_Object=comm.CRCGenerator('Polynomial',CRC_method, 'ChecksumsPerFrame',4);
%使用生成的CRC校验对象对声音数据流做处理
%注意这里的数据流要转化成logical模式
Voice_a_compressed_bitstream_CRC =step(CRC_Object,logical(Voice_a_compressed_bitstream));
%FSK/ASK/PSK/QPSK调制

%创建噪声对象
hAWGN = comm.AWGNChannel('NoiseMethod','Signal to noise ratio (SNR)','SNR',15);

% %PSK调制
% %创建PSK对象，8点调制方式，0偏移，bit输入
% PSKhModulator = comm.PSKModulator(2,0,'BitInput',true);
% %创建PSK解调对象
% PSKhDemod = comm.PSKDemodulator(2,0,'BitOutput',true);
% %调制信号
% modSignal = step(PSKhModulator, Voice_a_compressed_bitstream_CRC);
% %加入噪声
% % Pass the gauss channel with SNR=15dB，越小波形越乱
% noisySignal = awgn(modSignal,10,'measured'); 
% %解调
% receivedData=step(PSKhDemod, noisySignal);
% % constellation(PSKhModulator);

% %FSK
% %创建调制器
% FSKhMod = comm.FSKModulator(2,100);
% FSKhMod.BitInput=true;
% %创建解调器
% FSKhDemod = comm.FSKDemodulator(2, 100);
% FSKhDemod.BitOutput=true;
% FSKhDemod.OutputDataType='logical';
% %调制信号
% modSignal = step(FSKhMod, Voice_a_compressed_bitstream_CRC);
% %加入噪声
% noisySignal = step(hAWGN, modSignal);
% %解调信号
% receivedData = step(FSKhDemod, noisySignal);


% %QPSK
% % 创建QPSK调制对象 
% QPSKhModulator = comm.QPSKModulator('BitInput',true);
% %创建QPSK解调
% QPSKhDemod = comm.QPSKDemodulator('BitOutput',true);
% % 改变相位
% %  QPSKhModulator.PhaseOffset = pi/16;
% %根据创建的QPSK调制对象调制一段信号
% modSignal = step(QPSKhModulator, Voice_a_compressed_bitstream_CRC);
% %调制信号加入噪声                     
% noisySignal = step(hAWGN, modSignal);
% %将加入噪声的信号解调
% receivedData = step(QPSKhDemod, noisySignal); 
 
%PAM调制
% Create a 2-PAM modulator System object with bits as inputs and Gray-coded signal constellation
PAMhModulator = comm.PAMModulator(2,'BitInput',true);
PAMhDemod = comm.PAMDemodulator(2);
% Modulate and plot the data
modSignal = step(PAMhModulator, Voice_a_compressed_bitstream_CRC); 
% %加入噪声
noisySignal = step(hAWGN, modSignal);
% %解调信号
receivedData = step(PAMhDemod, noisySignal);
%constellation(PAMhModulator);


%绘制解调后的星座图
scatterplot(modSignal);
scatterplot(noisySignal);
scatterplot(receivedData);











