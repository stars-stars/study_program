import os
import datetime
import colorama as color

# ファイル名の設定
path = input("保存するファイル名を入力(拡張子を含まずに) << ")
path += ".txt"
while(os.path.exists(path)):
    print("このファイル名は既に存在しています")
    path = input("保存するファイル名を入力(拡張子を含まずに) << ")
    path += ".txt"


# 各問予想の入力
num_question = input("問題番号の始まりを入力 << ")
while(not num_question.isnumeric()):
    print("数値を入力してください")
    num_question = input("問題番号の始まりを入力 << ")
num_question = int(num_question)
num_start = num_question
print("\n各問の予想を入力\n")
print("exitで入力の終了, --- で入力の修正")
input_list = []
inputed = input(f"問{num_question}. << ")
while(inputed != "exit"):
    if(inputed == "---"):
        while(inputed == "---"):
            inputed = input("修正したい問題番号を入力 << ")
            while(not inputed.isnumeric()):
                print("数値を入力してください")
                inputed = input("修正したい問題番号を入力 << ")
            num = int(inputed)
            if(num >= (num_question)):
                print("入力済みの問題しか修正できません")
            else:
                inputed = input(f"(修正)問{num}の予想を入力 << ")
                input_list[num - num_start] = inputed
            inputed = input(f"問{num_question}. << ")
    else:
        input_list.append(inputed)
        num_question += 1
        inputed = input(f"問{num_question}. << ")


# 各問解答の入力
print("\n各問の解答を入力(--- で入力の修正)\n")
answer_list = []
for i in range(len(input_list)):
    inputed = input(f"問{i + num_start} の解答 << ")
    while(inputed == "---"):
        inputed = input("修正したい問題番号を入力 << ")
        while(not inputed.isnumeric()):
            print("数値を入力してください")
            inputed = input("修正したい問題番号を入力 << ")
        num = int(inputed)
        if(num >= (i + num_start)):
            print("入力済みの問題しか修正できません")
        else:
            inputed = input(f"(修正)問{num}の解答を入力 << ")
            answer_list[num - num_start] = inputed
        inputed = input(f"問{i + num_start} の解答 << ")
    answer_list.append(inputed)

corrected_answer = 0
is_correct = []
for i in range(len(input_list)):
    if(input_list[i] == answer_list[i]):
        corrected_answer += 1
        is_correct.append(True)
    else:
        is_correct.append(False)

# 結果の表示
print("\n------------------------------------------------")
print("問番号       正誤        予想        解答")
for i in range(len(input_list)):
    print("問" + format(i + num_start, "3d") + "         ", end="")
    if(is_correct[i]):
        print("○           ", end="")
    else:
        print("×           ", end="")
    print(f"{input_list[i]}          {answer_list[i]}")
print("------------------------------------------------\n")
print(color.Fore.CYAN)
print(f"\n正解数は{corrected_answer}, 正答率は{round(corrected_answer/len(input_list), 2)*100}%")
print(color.Fore.LIGHTGREEN_EX)
print("以下間違った問題")
for i in range(len(input_list)):
    if(not is_correct[i]):
        print(f"問{i + num_start}")

# ファイルへの書き込み
with open(path, "w") as f:
    f.write(f"{datetime.date.today()}\n")
    f.write(f"正解数は{corrected_answer}, 正答率は{round(corrected_answer/len(input_list), 2)*100}%\n")
    f.write("間違った問題は\n")
    for i in range(len(input_list)):
        if(not is_correct[i]):
            f.write(f"問{i + num_start}\n")
    f.write("\n\n------------------------------------------------\n")
    f.write("問番号       正誤        予想        解答\n")
    for i in range(len(input_list)):
        f.write("問" + format(i + num_start, "3d") + "         ")
        if(is_correct[i]):
            f.write("○           ")
        else:
            f.write("×           ")
        f.write(f"{input_list[i]}          {answer_list[i]}\n")
    f.write("------------------------------------------------\n")
print(f"\nファイル名 {path} で保存しました")
