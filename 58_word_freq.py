import sys,collections,re
if len(sys.argv)<2:
    print("Usage: python3 word_freq.py <file>"); sys.exit(1)
text=open(sys.argv[1]).read().lower()
words=re.findall(r"\b\w+\b", text)
c=collections.Counter(words)
for w,n in c.most_common():
    print(w,n)
