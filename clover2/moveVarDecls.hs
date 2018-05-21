module Main where


import System.Environment(getArgs)
-- import System
import Data.Generics
import Language.C
import Language.C.System.GCC

-- 第一引数のファイルを読み込み標準出力に出力
main = do
  (filename:[]) <- getArgs
  parseMyFile filename >>= (printMyAST . moveVarDecls)

-- Language.C を使ってソースを parse
parseMyFile :: FilePath -> IO CTranslUnit
parseMyFile input_file =
  do parse_result <- parseCFile (newGCC "gcc") Nothing [] input_file -- プリプロセスに使うgcc (cpp?) のパスを設定しよう
     case parse_result of
       Left parse_err -> error (show parse_err)
       Right ast      -> return ast

-- 表示
printMyAST :: CTranslUnit -> IO ()
printMyAST ctu = (print . pretty) ctu

-- Data.Generics (scrap your boilerplate) を使った、構文木のトラバース
moveVarDecls :: CTranslUnit -> CTranslUnit
moveVarDecls = everywhere (mkT moveVarDecls_)

-- ブロックの内容を宣言と代入文に分ける．
moveVarDecls_ :: [CBlockItem] -> [CBlockItem]
moveVarDecls_ bs = concat decls++concat stmts -- 宣言の後にブロックが来る
  where
    (decls,stmts) = unzip (map splitVarDecls bs)

-- 1つの変数宣言を宣言と代入文に分割する
splitVarDecls :: CBlockItem -> ([CBlockItem],[CBlockItem])
splitVarDecls (CBlockDecl (CDecl sp assign ninfo)) = ([mkDecl sp assign ninfo], mkStmts assign ninfo)
splitVarDecls x = ([],[x])

-- 宣言文から代入文を除去する．
-- sp 型、記憶子、修飾子のリスト
-- assign 変数名および代入文
-- ninfo ノード情報
mkDecl :: [CDeclSpec] -> [(Maybe CDeclr, Maybe CInit, Maybe CExpr)] -> NodeInfo -> CBlockItem
mkDecl sp assign ninfo = CBlockDecl (CDecl sp (map mkAssign assign) ninfo)
  where
    -- declr 変数名と、constやポインタ等の修飾子 (int *x; における *xの部分)
    -- init 代入文の右辺
    -- expr 構造体のフィールド宣言におけるビット長(ここではNothing)
    mkAssign (a@(_, Nothing, _)) = a 
    mkAssign (declr, Just init, expr) = (declr, Nothing, expr) -- 代入文を除去

-- 宣言文から代入文を抜き出す．
-- assign 変数名および代入文
-- ninfo ノード情報
mkStmts :: [(Maybe CDeclr, Maybe CInit, Maybe CExpr)] -> NodeInfo -> [CBlockItem]
mkStmts assign ninfo = concatMap mkExpr assign
  where
    mkExpr (Just (CDeclr (Just name) _ _ _ v_ninfo), Just (CInitExpr expr i_ninfo), _) 
      = [CBlockStmt (CExpr (Just (CAssign CAssignOp (CVar name v_ninfo) expr i_ninfo)) ninfo)] -- 代入文を生成
    mkExpr _ = []
