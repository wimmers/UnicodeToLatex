/* Util */
let js_replace = Js.String.replaceByRe;

let re_from_str = Js.Re.fromStringWithFlags;

let split_by = Js.String.splitByRe;

let split_by_limit = Js.String.splitByReAtMost;

let id = x => x;

let array_filter_map = (f, xs) => {
  let g = (xs, x) =>
    switch (f(x)) {
    | None => xs
    | Some(x) => [x, ...xs]
    };
  Array.fold_left(g, [], xs);
};

let binops = [({js|=|js}, "=")];

let binops_escape = [
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
  ({js|↦|js}, {|\mapsto|}),
  ({js|⤜|js}, {|\bind|}),
  ({js|≡|js}, {|\equiv|})
];

let binops_isabelle_hol = [
  ({js|#|js}, {|\cdot|}),
  ({js|===>|js}, {|\relfun|}),
  ({js|OO|js}, {|\relcomp|})
];

let binops_escape = List.append(binops_escape, binops_isabelle_hol);

let binops1 =
  List.map(
    x => ("\\s?" ++ fst(x) ++ "\\s?", snd(x)),
    List.append(binops, binops_escape)
  );

let binops2 =
  List.append(
    List.map(x => (snd(x), " " ++ snd(x) ++ " "), binops),
    List.map(x => ("\\" ++ snd(x), " " ++ snd(x) ++ " "), binops_escape)
  );

let greek_alphabet = [({js|Γ|js}, {|\Gamma|})];

let mathcals = [
  {js|𝒜|js},
  {js|ℬ|js},
  {js|𝒞|js},
  {js|𝒟|js},
  {js|ℰ|js},
  {js|ℱ|js},
  {js|𝒢|js},
  {js|ℋ|js},
  {js|ℐ|js},
  {js|𝒥|js},
  {js|𝒦|js},
  {js|ℒ|js},
  {js|ℳ|js},
  {js|𝒩|js},
  {js|𝒪|js},
  {js|𝒫|js},
  {js|𝒬|js},
  {js|ℛ|js},
  {js|𝒮|js},
  {js|𝒯|js},
  {js|𝒰|js},
  {js|𝒱|js},
  {js|𝒲|js},
  {js|𝒳|js},
  {js|𝒴|js},
  {js|𝒵|js}
];

let caps_alphabet =
  Array.to_list(Js.String.split("", {js|ABCDEFGHIJKLMNOPQRSTUVWXYZ|js}));

let mathcal = {
  let caps = List.map(s => {|\mathcal{|} ++ s ++ "}", caps_alphabet);
  Js.log(List.length(caps));
  let zipped = List.map2((a, b) => (a, b), mathcals, caps);
  zipped;
};

let isabelle_keywords = [
  ({js|datatype|js}, {|\isacommand{datatype}|}),
  ({js|fun|js}, {|\isacommand{fun}|}),
  ({js|proof|js}, {|\isacommand{proof}|}),
  ({js|qed|js}, {|\isacommand{qed}|}),
  ({js|inductive|js}, {|\isacommand{inductive}|}),
  ({js|where|js}, {|\isacommand{where}|}),
  ({js|if|js}, {|\isacommand{if}|}),
  ({js|for|js}, {|\isacommand{for}|}),
  ({js|assumes|js}, {|\isacommand{assumes}|}),
  ({js|assume|js}, {|\isacommand{assume}|}),
  ({js|shows|js}, {|\isacommand{shows}|}),
  ({js|show|js}, {|\isacommand{show}|}),
  ({js|obtains|js}, {|\isacommand{obtains}|}),
  ({js|obtain|js}, {|\isacommand{obtain}|})
];

let patterns = [
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
  ({js|〉|js}, {|\rangle|})
];

let patterns_first = [({js|_|js}, {|\_|})];

let patterns = List.append(binops2, List.append(patterns, binops1));

let patterns = List.append(greek_alphabet, patterns);

let patterns_last = [];

let patterns_last = List.append(mathcal, patterns_last);

let fallback_table = Array.to_list(Translation_table.unicode_to_latex);

let whitespace_patterns = space => [
  ({js|\\n|js}, "\\\\\n"),
  ({js| |js}, space)
];

let replace = patterns =>
  List.fold_right(
    (p, s) => js_replace(re_from_str(fst(p), "g"), snd(p), s),
    patterns
  );

let replace_fallback =
  List.fold_right(
    (p, s) => js_replace(re_from_str(fst(p), "g"), snd(p), s),
    fallback_table
  );

let replace_whitespace = space =>
  List.fold_right(
    (p, s) => js_replace(re_from_str(fst(p), "g"), snd(p), s),
    whitespace_patterns(space)
  );

let replace_keywords =
  List.fold_right(
    (p, s) => js_replace(re_from_str(fst(p), "g"), snd(p), s),
    isabelle_keywords
  );

let remove_quotations = js_replace(re_from_str({js|\\"|js}, "g"), "");

let bindings_of = str => {
  let f = p => Array.length(p) == 2 ? Some((p[0], p[1])) : None;
  let lines = split_by(re_from_str("\n", "g"), str);
  let bindings =
    Array.map(
      split_by_limit(re_from_str("\\s*\\:\\s*(.*)", "i"), ~limit=2),
      lines
    );
  let bindings = array_filter_map(f, bindings);
  bindings;
};

let replace_bindings = bindings => {
  let bindings = bindings_of(bindings);
  List.fold_right(
    (p, s) => js_replace(re_from_str(fst(p), "g"), snd(p), s),
    bindings
  );
};

let translate = (~flags: Flags.flag_state, text, bindings, space) => {
  let replace_opt = (flag, replace) =>
    Flags.flagSet(flag, flags) ? replace : id;
  text
  |> replace_opt(Whitespace, replace_whitespace(space))
  |> replace_opt(Fallback, replace_fallback)
  |> replace_opt(Isabelle_Keywords, replace_keywords)
  |> replace_opt(Remove_Quotations, remove_quotations)
  |> replace_bindings(bindings)
  |> replace(patterns)
  |> replace(patterns_last);
};