	% (C) Philip Pronin, 2008
% (C) Yury Kartynnik, 2010
% (C) Aliaksei Kolesau, 2016

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{bsureport}[2010/05/10]

\DeclareOption{draft}{
  \PassOptionsToClass{draft}{article}
  \AtEndOfClass{\geometry{showframe}}}
\DeclareOption{12pt}{\PassOptionsToClass{12pt}{extsizes}}
\DeclareOption{14pt}{\PassOptionsToClass{14pt}{extsizes}}
\DeclareOption{a3paper}{\setlength\paperheight{420mm}\setlength\paperwidth{297mm}}
\DeclareOption{a4paper}{\setlength\paperheight{297mm}\setlength\paperwidth{210mm}}
\DeclareOption{a5paper}{\setlength\paperheight{210mm}\setlength\paperwidth{148mm}}

\ProcessOptions

\LoadClass{article}
\RequirePackage{extsizes}
\RequirePackage[left=2cm,right=1cm,top=2cm,bottom=2cm,headsep=0pt]{geometry}

\pagestyle{plain}
\pagenumbering{arabic}

%\usepackage{chngcntr}
%\counterwithin{figure}{section}

\RequirePackage{polyglossia}
\setmainlanguage[babelshorthands=true]{russian}
\setotherlanguage{english}
\defaultfontfeatures{Ligatures=TeX,Mapping=tex-text}

\setmainfont[Ligatures=TeX]{Times New Roman}
\newfontfamily\cyrillicfont[Script=Cyrillic]{Times New Roman}
\newfontfamily\cyrillicfontrm[Script=Cyrillic]{Times New Roman}
\newfontfamily\cyrillicfontbf[Script=Cyrillic]{Times New Roman}
\newfontfamily\cyrillicfontsc[Script=Cyrillic]{Times New Roman}
\setmonofont{Courier New}
\newfontfamily\cyrillicfonttt{Courier New}

\RequirePackage[table]{xcolor}
\RequirePackage{amssymb,amsmath,amsthm}
\RequirePackage{float,indentfirst}
%\RequirePackage[pdftex]{graphicx}
\RequirePackage[unicode,pdfstartview=FitH,colorlinks=true,%
citecolor=black,linkcolor=black,filecolor=black,linkcolor=black,urlcolor=black]{hyperref}
\RequirePackage{tocloft}
\RequirePackage{enumerate}
\RequirePackage{tikz}
\RequirePackage{listings}
\RequirePackage{wrapfig}
\RequirePackage{url}
\RequirePackage[skip=3pt]{caption}
\RequirePackage{xltxtra}
\RequirePackage{tabularx}

\DeclareMathOperator{\prelu}{prelu}
\DeclareMathOperator{\softmax}{softmax}

\newcommand{\codefont}{\fontsize{10}{11}\ttfamily}

\lstset{language=C++,showstringspaces=false,extendedchars=true,%
basicstyle={\codefont},%
keywordstyle=\bfseries,%\color{blue!50!black},%
stringstyle=\itshape,%\color{red!50!black},%
commentstyle=\itshape,%\color{green!30!black}
}

\bibliographystyle{bib/gost71u2003}

\floatname{algorithm}{Алгоритм}
\newtheoremstyle{custom}
  {0pt}% measure of space to leave above the theorem. E.g.: 3pt
  {0pt}% measure of space to leave below the theorem. E.g.: 3pt
  {\normalfont}% name of font to use in the body of the theorem
  {\parindent}% measure of space to indent
  {\bfseries}% name of head font
  {.}% punctuation between head and body
  { }% space after theorem head; " " = normal interword space
  {\thmname{#1}\thmnumber{ #2}\thmnote{ (#3)}}% manually specify head
\theoremstyle{custom}
\newenvironment{Proof}{\par\textbf{Доказательство.} }{\qed}
\newtheorem{theorem}{Теорема}
\newtheorem{definition}{Определение}
\newtheorem{claim}[theorem]{Утверждение}
\newtheorem{cor}[theorem]{Следствие}
\newtheorem{lemma}[theorem]{Лемма}
\newtheorem{hypoth}{Гипотеза}

\newcommand\defd[1]{\emph{#1}}

\renewcommand\leq{\leqslant}
\renewcommand\geq{\geqslant}
\renewcommand\phi{\varphi}
\renewcommand\epsilon{\varepsilon}
\newcommand\eps{\varepsilon}
\renewcommand\emptyset{\varnothing}

\newenvironment{enum}
  {\begin{enumerate}[\indent 1. ]\addtolength{\itemsep}{-0.5\baselineskip}}
  {\end{enumerate}}

\newenvironment{items}
  {\begin{itemize}\addtolength{\itemsep}{-0.5\baselineskip}}
  {\end{itemize}}


\newcommand\sectionc{\@startsection{section}{1}{\z@}
  {-3.5ex \@plus -1ex \@minus -.2ex}
  {2.3ex \@plus.2ex}
  {\centering\normalfont\large\bfseries}}

\renewcommand\section{\@startsection{section}{1}{0pt}
  {-3.5ex \@plus -1ex \@minus -.2ex}
  {0.5ex \@plus.2ex}
  {\normalfont\large\bfseries\center    }}


\renewcommand\subsection{\@startsection{subsection}{1}{0pt}
  {-3.5ex \@plus -1ex \@minus -.2ex}
  {1ex \@plus.2ex}
  {\normalfont\large\bfseries}}

\renewenvironment{abstract}{\clearpage\sectionc*{\MakeUppercase{Реферат}}}{\clearpage}

\newenvironment{abstract:en}{\sectionc*{\MakeUppercase{Abstract}}\begin{otherlanguage}{english}}{\end{otherlanguage}}
\newenvironment{abstract:ru}{\sectionc*{\MakeUppercase{Аннотация}}}{}
\newenvironment{abstract:by}{\sectionc*{\MakeUppercase{Анатацыя}}}{}

\renewcommand{\thetable}{\arabic{table}}

\renewcommand{\fnum@figure}{Рисунок~\thefigure}
\renewcommand{\@makecaption}[2]{%
  \vspace{\abovecaptionskip}
  \sbox{\@tempboxa}{#1~- #2}%
  \ifdim \wd\@tempboxa >\hsize
    \centering\textbf{#1~--- #2}\par
  \else
    \global\@minipagefalse
    \hbox to \hsize {\hfil \textbf{#1~--- #2}\hfil}%
  \fi
  \vskip\belowcaptionskip}

\newenvironment{docpart}[1]
  {\clearpage\section{#1}}
  {\clearpage}

\newcounter{bibitem}
\newcommand{\thebibname}{СПИСОК ИСПОЛЬЗОВАННЫХ ИСТОЧНИКОВ}
\renewcommand{\@biblabel}[1]{#1. }
\renewenvironment{thebibliography}[1]{%
  \clearpage%
  \sectionc*{\thebibname}\addcontentsline{toc}{section}{\thebibname}%
  \@mkboth{\MakeUppercase\thebibname}{\MakeUppercase\thebibname}%
  \list{\@biblabel{\@arabic\c@bibitem}}%
    {\settowidth\labelwidth{\@biblabel{#1}}\leftmargin\labelwidth
      \advance\leftmargin\labelsep
      \@openbib@code
      \usecounter{bibitem}\let\p@enumiv\@empty
      \renewcommand\theenumiv{\@arabic\c@bibitem}}%
    \sloppy
    \clubpenalty4000
    \@clubpenalty \clubpenalty
    \widowpenalty4000\sfcode`\.\@m}
{\def\@noitemerr{%
  \@latex@warning{Empty `thebibliography' environment}}\endlist}


\newcounter{bsureport@pagenum}
\newcounter{bsureport@appnum}
\newcounter{bsureport@fignum}
\newcounter{bsureport@bibnum}
\newcounter{bsureport@tabnum}

\newcommand{\totalpages}{\arabic{bsureport@pagenum}}

\newcommand{\makestat}[1]{#1, \totalpages{} с.,
  \arabic{bsureport@tabnum} табл.,
  \arabic{bsureport@fignum} рис.,
  \arabic{bsureport@bibnum} источн.%,
%  \arabic{bsureport@appnum} прил.
}

\newcommand{\makestaten}[1]{#1, \totalpages{} p.,
  \arabic{bsureport@tabnum} tab.,
  \arabic{bsureport@fignum} fig.,
  \arabic{bsureport@bibnum} ref.%,
%  \arabic{bsureport@appnum} прил.
}

\def\lastpage@putlabel{
  \addtocounter{page}{-1}
  \immediate\write\@auxout{\string\setcounter{bsureport@pagenum}{\arabic{page}}}
  \addtocounter{page}{1}
  \immediate\write\@auxout{%
    \string\setcounter{bsureport@appnum}{\arabic{appendix}}}
  \immediate\write\@auxout{\string\setcounter{bsureport@bibnum}{\arabic{bibitem}}}
  \immediate\write\@auxout{\string\setcounter{bsureport@fignum}{\arabic{figure}}}
  \immediate\write\@auxout{\string\setcounter{bsureport@tabnum}{\arabic{table}}}
}
\AtEndDocument{\clearpage\lastpage@putlabel}

\renewcommand{\cfttoctitlefont}{\large\bfseries}

\renewcommand{\cftsecfont}{}
\renewcommand{\cftsecpagefont}{}
\renewcommand{\cftsecleader}{\cftdotfill{1}}
\setlength{\cftbeforesecskip}{0.25em}
\renewcommand{\cftsubsecfont}{}
\renewcommand{\cftsubsecpagefont}{}
\renewcommand{\cftsubsecleader}{\dotfill}
\setlength{\cftbeforesubsecskip}{0.25em}
\cftsetpnumwidth{1em}

%\renewcommand{\rmdefault}{ftm}

\setlength{\parskip}{2pt}

\newcounter{appendix}
\newcounter{file}
\renewenvironment{appendix}[1]{%
  \clearpage%
  \addtocounter{appendix}{1}%
  \sectionc*{ПРИЛОЖЕНИЕ \@Alph\c@appendix}%
  \addcontentsline{toc}{section}{ПРИЛОЖЕНИЕ \@Alph\c@appendix. #1}%
  \begin{center}\vskip -1em \large\textbf{#1}\end{center}%
  \setcounter{file}{0}%
}{}

\newcommand{\fig}[4][ht]%
               {\begin{figure}[#1]%
                \centering%
                #4
                \caption{#3}%
                \label{pic:#2}%
                \end{figure}%
               }

\usetikzlibrary{calc}
\usetikzlibrary{through}
\usetikzlibrary{positioning}

\newcommand{\pic}[4][ht]%
{\fig[#1]{#2}{#3}{%
				\noindent\makebox[\textwidth]{%
				\begin{tikzpicture}%
                	#4
                }%
                \end{tikzpicture}%
}}

\newcommand{\externpic}[4][ht]{\fig[#1]{#2}{#3}{\input{#4}}}

\newcommand{\img}[4][width=\textwidth]%
               {\begin{figure}[ht]%
                \noindent\makebox[\textwidth]{%
                \includegraphics[#1]{#4}%
                }%
                \caption{#3}%
                \label{img:#2}%
                \end{figure}%
               }


\newcommand{\includefile}[3]{%
   \addtocounter{file}{1}%
   \noindent\textbf{\@Alph\c@appendix.\arabic{file} Файл \textit{#1}~--- #2}
   \lstinputlisting{appendix/#3}%
   \vskip 1em%
}

\newcommand{\NPprobName}[1]{\textsc{#1}}
\newcommand{\NPproblem}[2]{\vspace*{0.5ex} \NPprobName{#1} \par #2 \vspace*{0.5ex}}


\newcommand{\comment}[1]{}
