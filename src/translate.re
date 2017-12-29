/* Util */
let js_replace = Js.String.replaceByRe;
let re_from_str = Js.Re.fromStringWithFlags;
let split_by = Js.String.splitByRe;
let split_by_limit = Js.String.splitByReAtMost;

let id = (x) => x;

let array_filter_map = (f, xs) => {
  let g = (xs, x) => switch (f(x)) {
  | None => xs
  | Some(x) => [x, ...xs]
  };
  Array.fold_left(g, [], xs)
};

let binops =
[
  ({js|=|js}, "="),
];

let binops_escape =
[
  ({js|⇒|js}, {|\Rightarrow|}),
  ({js|←|js}, {|\leftarrow|}),
  ({js|→|js}, {|\to|}),
  ({js|×|js}, {|\times|}),
  ({js|∧|js}, {|\wedge|}),
  ({js|⟶|js}, {|\longrightarrow|}),
  ({js|⟹|js}, {|\Longrightarrow|}),
  ({js|⟷|js}, {|\longleftrightarrow|}),
  ({js|∈|js}, {|\in|}),
  ({js|⊆|js}, {|\subseteq|}),
  ({js|∩|js}, {|\cap|}),
  ({js|∪|js}, {|\cup|}),
  ({js|≤|js}, {|\leq|}),
  ({js|#|js}, {|\cdot|}),
  ({js|↦|js}, {|\mapsto|}),
  ({js|⤜|js}, {|\bind|}),
  ({js|≡|js}, {|\equiv|}),
  ({js|===>|js}, {|\relfun|}),
  ({js|OO|js}, {|\relcomp|}),
];

let binops1 =
	List.map(x => ("\s?" ++ fst(x) ++ "\s?", snd(x)), List.append(binops, binops_escape));

let binops2 =
	List.append(
    List.map(x => (snd(x), " " ++ snd(x) ++ " "), binops),
	List.map(x => ("\\" ++ snd(x), " " ++ snd(x) ++ " "), binops_escape)
    );

let greek_alphabet =
[
  ({js|Γ|js}, {|\Gamma|}),
];

let isabelle_keywords =
[
  ({js|datatype|js}, {|\isacommand{datatype}|}), 
];

let patterns =
[
  ({js|⋀|js}, {|\bigwedge |}),
  ({js|∀|js}, {|\forall |}),
  ({js|∃|js}, {|\exists |}),
  ({js|\\{|js}, {|\{|}),
  ({js|\\.\\.|js}, {|\ldots |}),
  ({js|\\}|js}, {|\}|}),
  ({js|∞|js}, {|\infty|}),
  ({js|λ|js}, {|\lambda |}),
  ({js|⇩|js}, {|_|}),
  ({js|⇩|js}, {|_|}),
  ({js|⟩|js}, {|\rangle |}),
  ({js|⟨|js}, {|\langle |}),
  ({js|〈|js}, {|\langle|}),
  ({js|_|js}, {|\_|}),
];

let patterns = List.append(binops2, List.append(patterns, binops1));
let patterns = List.append(greek_alphabet, patterns);

let whitespace_patterns =
[
  ({js|\\n|js}, "\\\\\n"),
  ({js| |js}, {|~|}),
];

let replace = List.fold_right (
  (p,s) => js_replace(re_from_str(fst(p),"g"), snd(p), s),
  patterns
);

let replace_whitespace = List.fold_right (
  (p,s) => js_replace(re_from_str(fst(p),"g"), snd(p), s),
  whitespace_patterns
);

let replace_keywords = List.fold_right (
  (p,s) => js_replace(re_from_str(fst(p),"g"), snd(p), s),
  isabelle_keywords
);

let remove_quotations =
  js_replace(re_from_str({js|\\"|js},"g"), "");

let bindings_of = str => {
  let f = (p) =>
    Array.length(p) == 2 ?
    Some((p[0], p[1])) :
    None;
  let lines = split_by(re_from_str("\n", "g"), str);
  let bindings = Array.map(split_by_limit(re_from_str("\s*\:\s*(.*)", "i"), ~limit=2), lines);
  let bindings = array_filter_map(f, bindings);
  bindings
};

let replace_bindings = (bindings) => {
  let bindings = bindings_of(bindings);
  List.fold_right (
    (p,s) => js_replace(re_from_str(fst(p),"g"), snd(p), s),
    bindings
  );
};

let translate = (~flags: Flags.flag_state, text, bindings) => {
  text
  |> (Flags.flagSet(Whitespace, flags) ? replace_whitespace : id)
  |> (Flags.flagSet(Isabelle_Keywords, flags) ? replace_keywords : id)
  |> (Flags.flagSet(Remove_Quotations, flags) ? remove_quotations : id)
  |> replace_bindings(bindings)
  |> replace
}