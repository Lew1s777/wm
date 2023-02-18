static void selectlayout(const Arg *arg);
static void incnmaster(const Arg *arg);

void
selectlayout(const Arg *arg)
{
    const Layout *cur = selmon->lt[selmon->sellt];
    const Layout *target = cur == arg->v ? &layouts[0] : arg->v;
    setlayout(&(Arg) { .v = target });
}

void
incnmaster(const Arg *arg)
{
    int nmaster = selmon->nmaster + arg->i;
    if (selmon->bt <= 1)
        nmaster = 1;
    else if (nmaster >= 3)
        nmaster = 1;
    selmon->nmaster = selmon->pertag->nmasters[selmon->pertag->curtag] = MAX(nmaster, 1);
    arrange(selmon);
}
