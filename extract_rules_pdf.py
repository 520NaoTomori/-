# -*- coding: utf-8 -*-
"""Extract text from the 2026 FS rules PDF (quiz version)."""
import sys

src = r"E:\xwechat_files\wxid_ju544l3sfgmv22_15c3\msg\file\2026-08\2026中国大学生方程式系列赛事规则（答题版）.pdf"
out = r"E:\自研BMS和软件资料\E42_优化\赛事规则_答题版_文本.txt"

try:
    import pdfplumber
    HAVE_PDFPLUMBER = True
except Exception:
    HAVE_PDFPLUMBER = False

try:
    from pypdf import PdfReader
    HAVE_PYPDF = True
except Exception:
    try:
        from PyPDF2 import PdfReader
        HAVE_PYPDF = True
    except Exception:
        HAVE_PYPDF = False

if not (HAVE_PDFPLUMBER or HAVE_PYPDF):
    print("NO_PDF_LIB")
    sys.exit(1)

if HAVE_PDFPLUMBER:
    with pdfplumber.open(src) as pdf:
        n = len(pdf.pages)
        print("PAGES", n)
        with open(out, "w", encoding="utf-8") as f:
            for i, page in enumerate(pdf.pages):
                txt = page.extract_text() or ""
                f.write(f"\n===== PAGE {i+1} =====\n")
                f.write(txt)
                if i % 20 == 0:
                    print("page", i + 1, "chars", len(txt))
else:
    reader = PdfReader(src)
    n = len(reader.pages)
    print("PAGES", n)
    with open(out, "w", encoding="utf-8") as f:
        for i, page in enumerate(reader.pages):
            txt = page.extract_text() or ""
            f.write(f"\n===== PAGE {i+1} =====\n")
            f.write(txt)
            if i % 20 == 0:
                print("page", i + 1, "chars", len(txt))

print("DONE")
