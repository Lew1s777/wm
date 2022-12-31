static void incnmaster(const Arg *arg);

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
