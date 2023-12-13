
import pickle 
import argparse
from time import time


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("index_file", help="output file")
    args = parser.parse_args()
    return args



def load_index(output_file):
    f = open(output_file, "r") 
    n_words = int(f.readline())
    index = {}

    for i in range(n_words):
        word = f.readline().strip()
        index[word] = {}

        n_docs = int(f.readline())

        for j in range(n_docs):
            doc, freq = f.readline().split()
            index[word][doc] = int(freq)            

    f.close()

    return index


def search_docs(index, query):
    start = time()
    
    # separa as palavras da query
    words = query.split()
    
    # remove palavras repetidas 
    words = list(set(words))

    # documentos recomendados e respectivas relevancias
    recommendations = {}

    # para cada palavra da query 
    for w in words:
        # obtem a lista de documentos em que a palavra aparece e as respectivas frequencias 
        docs_freqs = index.get(w)
        # se a palavra nao esta no indice, passamos para a proxima palavra
        if docs_freqs is not None:
            # se ela existe, para cada documento e frequencia...
            for doc, freq in docs_freqs.items():
                # ... se o documento ainda nao esta na lista de recomendacoes, adicionamos ele com a frequencia
                if doc not in recommendations:
                    recommendations[doc] = freq 
                # ... caso contrario, somamos a frequencia do documento com a frequencia ja existente
                else:
                    recommendations[doc] += freq 

    end = time()

    print(f"Tempo de busca: {end - start:.3f} segundos")

    # converte a hash em uma lista de pares (nome_documento, frequencias), e.g., 
    # [(doc1, 120), (doc2, 30), (doc3, 50), ...]
    recommendations = recommendations.items()

    # ordena os documentos pela frequencia com os mais relevantes primeiro
    recommendations = sorted(recommendations, key=lambda x: x[1], reverse=True)

    return recommendations


def print_output(docs):
    for doc, freq in docs[:10]:
        print(f"{doc}: {freq}")
    

def main():
    args = parse_args()
    index = load_index(args.index_file)
    query = input("Query: ")
    docs = search_docs(index, query)
    print_output(docs)
    

if __name__  == "__main__":
    main()