type flag = Debug | Fallback | Isabelle_HOL | Isabelle_Keywords | Remove_Quotations | Show_Settings | Whitespace;

type flag_state = {
    debug: bool,
    fallback: bool,
    isabelle_hol: bool,
    isabelle_keywords: bool,
    remove_quotations: bool,
    show_settings: bool,
    whitespace: bool,
};

let initial_flags = {
    debug: false,
    fallback: true,
    isabelle_hol: false,
    isabelle_keywords: false,
    remove_quotations: false,
    show_settings: false,
    whitespace: true
};

let toggleFlag = (flag, state) => switch flag {
    | Debug => {...state, debug: !state.debug}
    | Fallback => {...state, fallback: !state.fallback}
    | Isabelle_HOL => {...state, isabelle_hol: !state.isabelle_hol}
    | Isabelle_Keywords => {...state, isabelle_keywords: !state.isabelle_keywords}
    | Remove_Quotations => {...state, remove_quotations: !state.remove_quotations}
    | Show_Settings => {...state, show_settings: !state.show_settings}
    | Whitespace => {...state, whitespace: !state.whitespace}
  };
  
let flagSet = (flag, state) => switch flag {
    | Debug => state.debug
    | Fallback => state.fallback
    | Isabelle_HOL => state.isabelle_hol
    | Isabelle_Keywords => state.isabelle_keywords
    | Remove_Quotations => state.remove_quotations
    | Show_Settings => state.show_settings
    | Whitespace => state.whitespace
};