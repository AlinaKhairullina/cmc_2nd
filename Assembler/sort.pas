program sort;
type mas = array[1..100] of integer;
var nc1, nc2, np1, np2, n, k, i: integer;
    x1, x2 : mas;
procedure genmas(n, k: integer; var a : mas); {Генерация массива}
var i: integer;
begin
if k = 1 then begin {от заданного параметра создаем конкретный массив}
a[1]:=random(100);
for i := 2 to n do 
    a[i] := a[i-1] - random(100);{Следующий элемент точно меньше предыдущего}
end;
if k = 2 then begin
a[1]:=random(100);
for i := 2 to n do 
    a[i] := a[i-1] + random(100);{}
end;
if (k = 3) or (k = 4) then
begin
for i:=1 to n do
    a[i] := random(100){Случайная расстановка элементов}
end
end;

procedure selection(n: integer; var a : mas);
var i, mx, j, m  :integer;
begin 
{Ищем максимум среди n-i+1 элементов}
for i:= 1 to n-1 do
    begin
    mx := a[i];
    for j:= i + 1 to n do
        begin
        nc1 := nc1 + 1;{количество cравнений увеличиваем}
        if a[j] > mx then 
            begin
            m  := j; 
            mx := a[j]
            end
        end;
    if (a[i] <> mx) then 
        begin
        a[m] := a[i];{меняем местами i-ый и максимальный, находящийся на k-ой позиции}
        a[i] := mx;
        np1 := np1 + 1;{количество перестановок увеличиваем}
        end;
    end;
end;


procedure shell(n: integer; var a: mas);
var l, i, j, q : integer;
begin
l := n div 2;{находим количество частей, а также расстояние между элементами, которое будем сравнивать}
while l > 0 do
    begin
    for i := l + 1 to n do 
        begin
        j := i;
        while (j > l) and (a[j] > a[j-l]) do {пока есть элемент, который есть в последовательности и если есть инверсия, то меняем элемпенты }
            begin
            q := a[j];
            a[j] := a[j -l];
            a[j-l] := q;
            j:= j - l;
            np2 := np2 + 1;
             nc2:= nc2 + 1;
            end;
        nc2 := nc2 + 1;
  
        end;
    l := l div 2 ;{изменяем шаг между элементами}
    end
end;
BEGIN 
readln(n, k);
nc1:=0; np1:=0; nc2:=0; np2:=0;
for i:=1 to n do x1[i] := 0;
genmas(n, k, x1);{генерация массива}
for i:=1 to n do x2[i] := x1[i];{дублируем массив}
for i:=1 to n do write(x1[i], ' ');
writeln();
selection(n, x1); {сортировка методом простого выбора}
for i:=1 to n do write(x1[i], ' ');
writeln();
writeln('Сортировка методом простого выбора');
writeln('Количество сравнений = ', nc1);
writeln('Количество перестановок = ', np1);
for i:=1 to n do write(x2[i], ' ');
writeln();
shell(n, x2);{сортировка методом Шелла}
for i:=1 to n do write(x2[i], ' ');
writeln();
writeln('Сортировка методом Шелла');
writeln('Количество сравнений = ', nc2);
writeln('Количество перестановок = ', np2)
END.
