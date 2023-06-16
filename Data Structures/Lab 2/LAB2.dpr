Program LAB2;

{$APPTYPE CONSOLE}

Const
  N = 64;

Type
  Pt = ^Elem;
  Elem = Record
    Data: Integer;
    Next: Pt;
    Prev: Pt;
  end;

Var
  First: Pt;
  K,I: Integer;

Procedure Input (Var Param: Integer);
Var
  Check: String;
  Error: Integer;
begin
  repeat
    readln(Check);
    val(Check,Param,Error);
    if (Error <> 0) or (Param <= 0) then
      writeln('Incorrect input');
  until (Error = 0) and (Param > 0);
end;


Procedure Make (Var X: Pt; N: Integer);
Var
  I: Integer;
  Y,Tmp: Pt;
begin
  new(X);
  Tmp:=X;
  for I := 1 to N - 1 do
  begin
    Y := X;
    New(X);
    Y^.Data := I;
    Y^.Next := X;
    X^.Prev := Y;
  end;
  X^.Next := Tmp;
  X^.Data := N;
  Tmp^.Prev := X;
  X := Tmp;
end;

Procedure Step (Var X: Pt; Num: Integer);
Var
  I: Integer;
begin
  for I := 1 to Num - 1 do
    X := X^.Next;
end;

Procedure DeleteElem (X: Pt; Num,Stp: Integer);
begin
  write('(',Num,') ');
  while Num > 1 do
  begin
    Step(X,Stp);
    write(X^.Data,' ');
    X^.Prev^.Next := X^.Next;
    X^.Next^.Prev := X^.Prev;
    X := X^.Next;
    Dec(Num);
  end;
  writeln('[',X^.Data,']');
end;

Begin
  write('Enter step : ');
  Input(K);
  for I := 1 to N do
  begin
    Make(First,I);
    DeleteElem(First,I,K);
  end;
  readln;
end.
