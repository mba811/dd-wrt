// This file was automatically generated by localedef.

package gnu.java.locale;

import java.util.ListResourceBundle;

public class LocaleInformation_cs_CZ extends ListResourceBundle
{
  static final String decimalSeparator = ",";
  static final String groupingSeparator = "\u00A0";
  static final String numberFormat = "#,###,##0.###";
  static final String percentFormat = "#,###,##0%";
  static final String[] weekdays = { null, "Ned\u011Ble", "Pond\u011Bl\u00ED", "\u00DAter\u00FD", "St\u0159eda", "\u010Ctvrtek", "P\u00E1tek", "Sobota" };

  static final String[] shortWeekdays = { null, "Ne", "Po", "\u00DAt", "St", "\u010Ct", "P\u00E1", "So" };

  static final String[] shortMonths = { "led", "\u00FAno", "b\u0159e", "dub", "kv\u011B", "\u010Den", "\u010Dec", "srp", "z\u00E1\u0159", "\u0159\u00EDj", "lis", "pro", null };

  static final String[] months = { "leden", "\u00FAnor", "b\u0159ezen", "duben", "kv\u011Bten", "\u010Derven", "\u010Dervenec", "srpen", "z\u00E1\u0159\u00ED", "\u0159\u00EDjen", "listopad", "prosinec", null };

  static final String[] ampms = { "", "" };

  static final String shortDateFormat = "dd.MM.yyyy";
  static final String defaultTimeFormat = "hh:m:s";
  static final String currencySymbol = "K\u010D";
  static final String intlCurrencySymbol = "CZK";
  static final String currencyFormat = "#,###,##0.00 $;-#,###,##0.00 $";

  private static final Object[][] contents =
  {
    { "weekdays", weekdays },
    { "shortWeekdays", shortWeekdays },
    { "shortMonths", shortMonths },
    { "months", months },
    { "ampms", ampms },
    { "shortDateFormat", shortDateFormat },
    { "defaultTimeFormat", defaultTimeFormat },
    { "currencySymbol", currencySymbol },
    { "intlCurrencySymbol", intlCurrencySymbol },
    { "currencyFormat", currencyFormat },
    { "decimalSeparator", decimalSeparator },
    { "groupingSeparator", groupingSeparator },
    { "numberFormat", numberFormat },
    { "percentFormat", percentFormat },
  };

  public Object[][] getContents () { return contents; }
}
