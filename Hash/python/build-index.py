
import pickle 
import argparse
from time import time


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("dir", help="input file")
    parser.add_argument("output_file", help="output file")
    args = parser.parse_args()
    
    return args


def build_file_names(dir_name):
    FILE_LIST_FILE_NAME = "files.txt"

    file_name = f"{dir_name}/{FILE_LIST_FILE_NAME}"

    with open(file_name, "r") as f:
        lines = f.readlines()

    # Remove newlines and add dir name to all lines
    lines = [f"{dir_name}/{line.strip()}" for line in lines]

    return lines


def read_file(file_name):
    with open(file_name, "r") as f:
        data = f.read()
    return data.split()


def build_index(files):
    start = time()
    
    index = {}
    # para cada arquivo na lista de arquivos
    for file_name in files:
        # le o conteudo do arquivo e separa as palavras
        words = read_file(file_name)
        # para cada palavra 
        for word in words:
            # se a palavra ja esta no indice
            if word in index:
                # se ja vimos a palavra no documento
                if file_name in index[word]:
                    # incrementamos a frequencia
                    index[word][file_name] += 1
                else:
                    # caso contrario, adicionamos o documento com frequencia inicial 1
                    index[word][file_name] = 1
            else:
                # se a palavra nao esta no indice, adicionamos ela 
                index[word] = {}
                # em seguida, associamos a palavra o documento com frequencia inicial 1
                index[word][file_name] = 1

    end = time()
    print(f"Index built in {end - start:.3f} seconds")

    return index


def save_index(index, output_file):
    f = open(output_file, "w") 

    n_words = len(index)
    f.write(str(n_words) + "\n")

    for word, docs_freqs in index.items():
        f.write(word + "\n")

        n_docs = len(docs_freqs)
        f.write(str(n_docs) + "\n")
        
        for doc, freq in docs_freqs.items():
            f.write(f"{doc} {freq}\n")

    f.close()
        


def main():
    args = parse_args()
    files = build_file_names(args.dir)
    index = build_index(files)
    save_index(index, args.output_file)


if __name__  == "__main__":
    main()