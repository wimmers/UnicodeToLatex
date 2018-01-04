/* Util */
let str = ReasonReact.stringToElement;
let to_js_bool = Js.Boolean.to_js_boolean;

let component = ReasonReact.statelessComponent("FlagBox");

let make = (~flags, ~flag, ~title, ~onToggle, ~hidden, _children) => {
...component,
render: (self) =>
    hidden ?
    ReasonReact.nullElement :
    <div className="item">
    <input
        _type="checkbox"
        checked=(to_js_bool(Flags.flagSet(flag, flags)))
        onChange=((_evt) => onToggle(flag)())
    />
    (str(title))
    </div>
};