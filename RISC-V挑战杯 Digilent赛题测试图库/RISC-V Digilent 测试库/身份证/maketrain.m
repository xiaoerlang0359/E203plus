R = x7(:,:,1);
thresh=graythresh(R);
R1 = imbinarize(R,thresh);
train0_0 = R1(151:187,56:76);
train1_0 = R1(151:187,77:97);
train2_0 = R1(151:187,98:118);
train3_0 = R1(151:187,119:139);
train4_0 = R1(151:187,140:160);
train5_0 = R1(151:187,161:181);
train6_0 = R1(151:187,182:202);
train7_0 = R1(151:187,203:223);
train8_0 = R1(151:187,224:244);
train9_0 = R1(151:187,245:265);
train0_1 = R1(151:187,266:286);
train1_1 = R1(151:187,287:307);
train2_1 = R1(151:187,308:328);
train3_1 = R1(151:187,329:349);
train4_1 = R1(151:187,350:370);
train5_1 = R1(151:187,371:391);
train6_1 = R1(151:187,392:412);
trainX_0 = R1(151:187,413:433);

% G1=imbinarize(G,thresh);
% test0 = G1(135:171,47:68);
% test1 = G1(135:171,69:90);
% test2 = G1(135:171,91:112);
% test3 = G1(135:171,113:134);
% test4 = G1(135:171,135:156);
% test5 = G1(135:171,157:178);
% test6 = G1(135:171,179:200);
% test7 = G1(135:171,201:222);
% test8 = G1(135:171,223:244);
% test9 = G1(135:171,245:266);
% testX = G1(135:171,421:442);
% 
% diff0_0 = abs(testX-train0_0);
% diff0_1 = abs(testX-train1_0);
% diff0_2 = abs(testX-train2_0);
% diff0_3 = abs(testX-train3_0);
% diff0_4 = abs(testX-train4_0);
% diff0_5 = abs(testX-train5_0);
% diff0_6 = abs(testX-train6_0);
% diff0_7 = abs(testX-train7_0);
% diff0_8 = abs(testX-train8_0);
% diff0_9 = abs(testX-train9_0);
% diff0_X = abs(testX-trainX_0);
% 
% sum0_0 = sum(sum(diff0_0))
% sum0_1 = sum(sum(diff0_1))
% sum0_2 = sum(sum(diff0_2))
% sum0_3 = sum(sum(diff0_3))
% sum0_4 = sum(sum(diff0_4))
% sum0_5 = sum(sum(diff0_5))
% sum0_6 = sum(sum(diff0_6))
% sum0_7 = sum(sum(diff0_7))
% sum0_8 = sum(sum(diff0_8))
% sum0_9 = sum(sum(diff0_9))
% sum0_X = sum(sum(diff0_X))


% R2 = x2(:,:,1);
% thresh=graythresh(R2);
% R2 = imbinarize(R2,thresh);
% train9_1 = R2(135:171,47:68);
% 
% diff9_0 = abs(train9_1-train0_0);
% diff9_1 = abs(train9_1-train1_0);
% diff9_2 = abs(train9_1-train2_0);
% diff9_3 = abs(train9_1-train3_0);
% diff9_4 = abs(train9_1-train4_0);
% diff9_5 = abs(train9_1-train5_0);
% diff9_6 = abs(train9_1-train6_0);
% diff9_7 = abs(train9_1-train7_0);
% diff9_8 = abs(train9_1-train8_0);
% diff9_9 = abs(train9_1-train9_0);
% diff9_X = abs(train9_1-trainX_0);
% 
% 
% 
% train7_1 = R2(135:171,69:90);
% diff9_0 = abs(train7_1-train0_0);
% diff9_1 = abs(train7_1-train1_0);
% diff9_2 = abs(train7_1-train2_0);
% diff9_3 = abs(train7_1-train3_0);
% diff9_4 = abs(train7_1-train4_0);
% diff9_5 = abs(train7_1-train5_0);
% diff9_6 = abs(train7_1-train6_0);
% diff9_7 = abs(train7_1-train7_0);
% diff9_8 = abs(train7_1-train8_0);
% diff9_9 = abs(train7_1-train9_0);
% diff9_X = abs(train7_1-trainX_0);
% 
% 
fid=fopen('train0_0.txt','w');
for i=1:37
    for j=1:21
         fprintf(fid,'%d',train0_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train1_0.txt','w');
    for i=1:37
     for j=1:21
         fprintf(fid,'%d',train1_0(i,j));
     end
     fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train2_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train2_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train3_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train3_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train4_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train4_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train5_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train5_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train6_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train6_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train7_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train7_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train8_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train8_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('train9_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',train9_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
fid=fopen('trainX_0.txt','w');
for i=1:37
    for j=1:21
        fprintf(fid,'%d',trainX_0(i,j));
    end
    fprintf(fid,'\n');
end
fclose(fid);
