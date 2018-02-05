MapPerm = perms([1,2,3,4]);
permLen = size(MapPerm,1);
leftHashMap = containers.Map;
rightHashMap = containers.Map;
count = 1;
tic;
for i = 1:permLen
    m1 = MapPerm(i,:);
    for j = 1:permLen
        m2 = MapPerm(j,:);
        for k =1:permLen
            m3 = MapPerm(k,:);
            leftKey = mat2str(sort([m1;m2;m3]));
            leftHashMap(leftKey)=1;
            for m = 1:permLen
                n1 = MapPerm(m,:);
                for n = 1:permLen
                    n2 = MapPerm(n,:);
                    for p = 1:permLen
                        n3 = MapPerm(p,:);
                        rigthKey = mat2str(sort([n1;n2;n3]));
                        rightHashMap(rigthKey)=1;
                        if ~isKey(leftHashMap,rigthKey) || ~isKey(rightHashMap,leftKey)
                            count = count+1;
                            disp(count);
                            disp([[m1;m2;m3];[n1;n2;n3]]);
                        end
                    end
                end
            end
        end
    end
end
toc;