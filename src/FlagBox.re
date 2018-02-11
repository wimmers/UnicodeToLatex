/* Imports */
open Util;

let component = ReasonReact.statelessComponent("FlagBox");

let make = (~flags, ~flag, ~title, ~onToggle, ~hidden=false, _children) => {
  ...component,
  render: self =>
    hidden ?
      ReasonReact.nullElement :
      <div className="item">
        <input
          _type="checkbox"
          checked=(to_js_bool(Flags.flagSet(flag, flags)))
          onChange=(_evt => onToggle(flag, ()))
        />
        (str(title))
      </div>
};